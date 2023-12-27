use std::{
    sync::{
        atomic::{AtomicBool, AtomicI64, Ordering},
        Arc, Mutex,
    },
    time::Duration,
};

use log::info;

use crate::{
    callback,
    client::{
        tests::{
            test_client::{TestCallbackImpl, TestMessageCakllbackImpl},
            TEST_ENDPOINT,
        },
        Client,
    },
    models::GetChatLogsResult,
    request::ChatRequest,
    services::auth::login_with_password,
    utils::{check_until, init_log},
};

#[tokio::test]
async fn test_client_fetch_logs() {
    let info = login_with_password(
        TEST_ENDPOINT.to_string(),
        "bob".to_string(),
        "bob:demo".to_string(),
    )
    .await;
    let c = Client::new("".to_string(), "".to_string(), &info.unwrap());
    let topic_id = "bob:alice";

    let local_logs = c.store.get_chat_logs("bob:alice", None, 10).unwrap();
    assert_eq!(local_logs.items.len(), 0);
    let mut last_seq = 0;
    let send_count = 2;
    for i in 0..send_count {
        let req = ChatRequest::new_text(topic_id, &format!("hello from rust unittest {}", i));
        let resp = c
            .send_chat_request(topic_id.to_string(), req)
            .await
            .unwrap();
        last_seq = resp.seq;
    }
    struct TestSyncLogsCallbackImpl {
        result: Arc<Mutex<Option<GetChatLogsResult>>>,
    }

    impl callback::SyncChatLogsCallback for TestSyncLogsCallbackImpl {
        fn on_success(&self, r: GetChatLogsResult) {
            let mut result = self.result.lock().unwrap();
            result.replace(r);
        }
        fn on_fail(&self, _reason: crate::Error) {
            panic!("on_fail {:?}", _reason);
        }
    }
    let result = Arc::new(Mutex::new(None));

    let cb = TestSyncLogsCallbackImpl {
        result: result.clone(),
    };

    c.sync_chat_logs(topic_id.to_string(), None, send_count, Box::new(cb));

    check_until(Duration::from_secs(3), || result.lock().unwrap().is_some())
        .await
        .unwrap();

    let r = result.lock().unwrap().take().unwrap();
    let local_logs = c.store.get_chat_logs(topic_id, None, send_count).unwrap();
    assert_eq!(r.start_seq, local_logs.start_sort_value);
    assert_eq!(r.end_seq, local_logs.end_sort_value);
    assert_eq!(last_seq, local_logs.start_sort_value);
}

#[tokio::test]
async fn test_client_recall_log() {
    init_log("INFO".to_string(), true);
    let info = login_with_password(
        TEST_ENDPOINT.to_string(),
        "vitalik".to_string(),
        "vitalik:demo".to_string(),
    )
    .await;

    let c = Client::new("".to_string(), "".to_string(), &info.unwrap());
    let recv_message_count = Arc::new(AtomicI64::new(0));
    c.set_callback(Some(Box::new(TestCallbackImpl {
        last_topic_id: Arc::new(Mutex::new("".to_string())),
        is_connected: Arc::new(AtomicBool::new(false)),
        is_recv_message: Arc::new(AtomicBool::new(false)),
        recv_message_count: recv_message_count.clone(),
        is_update_conversation: Arc::new(AtomicBool::new(false)),
    })));

    c.connect().await;

    check_until(Duration::from_secs(3), || {
        c.connection_status() == "connected"
    })
    .await
    .unwrap();
    let conversation = c.create_chat("alice".to_string()).await.unwrap();
    let topic_id = conversation.topic_id;
    let mut first_send_id = "".to_string();
    let mut last_send_id = "".to_string();

    let send_count = 2;
    let mut last_seq = 0;
    for i in 0..send_count {
        let req = ChatRequest::new_text(&topic_id, &format!("hello from rust unittest {}", i));
        let resp = c
            .send_chat_request(topic_id.to_string(), req)
            .await
            .unwrap();
        if i == 0 {
            first_send_id = resp.chat_id;
        } else {
            last_send_id = resp.chat_id;
        }
        last_seq = resp.seq;
    }
    check_until(Duration::from_secs(3), || {
        recv_message_count.load(Ordering::Relaxed) as u32 == send_count
    })
    .await
    .unwrap();

    info!("do recall first_send_id {}", first_send_id);

    let is_sent = Arc::new(AtomicBool::new(false));
    let is_ack = Arc::new(AtomicBool::new(false));

    let msg_cb = Box::new(TestMessageCakllbackImpl {
        is_sent: is_sent.clone(),
        is_ack: is_ack.clone(),
        last_error: Arc::new(Mutex::new("".to_string())),
    });

    let recall_id = c
        .do_recall(topic_id.to_string(), first_send_id.clone(), Some(msg_cb))
        .await
        .unwrap();

    check_until(Duration::from_secs(3), || is_ack.load(Ordering::Relaxed))
        .await
        .unwrap();

    struct TestSyncLogsCallbackImpl {
        result: Arc<Mutex<Option<GetChatLogsResult>>>,
    }

    impl callback::SyncChatLogsCallback for TestSyncLogsCallbackImpl {
        fn on_success(&self, r: GetChatLogsResult) {
            let mut result = self.result.lock().unwrap();
            result.replace(r);
        }
        fn on_fail(&self, _reason: crate::Error) {
            panic!("on_fail {:?}", _reason);
        }
    }

    let result = Arc::new(Mutex::new(None));
    let cb = TestSyncLogsCallbackImpl {
        result: result.clone(),
    };

    c.sync_chat_logs(
        topic_id.to_string(),
        Some(last_seq),
        send_count + 1,
        Box::new(cb),
    );

    check_until(Duration::from_secs(3), || result.lock().unwrap().is_some())
        .await
        .unwrap();

    let local_logs = c
        .store
        .get_chat_logs(&topic_id, None, send_count + 1)
        .unwrap();
    for item in local_logs.items.iter() {
        info!("item: {:?}", item);
    }
    assert_eq!(local_logs.items.len(), (send_count + 1) as usize);
    assert_eq!(local_logs.items[0].id, recall_id);
    assert_eq!(local_logs.items[1].id, first_send_id);
    assert!(local_logs.items[1].recall);
    assert_eq!(local_logs.items[2].id, last_send_id);
}
