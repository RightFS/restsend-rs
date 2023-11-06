mod client;
mod error;
mod migrate;
mod models;
mod net;
mod request;
#[cfg(test)]
mod tests;

mod utils;
use log::debug;
use std::io::Write;

pub const USER_AGENT: &str = "restsend/0.1.0"; // ios/android
const CHAT_ID_LEN: usize = 10;
const REQ_ID_LEN: usize = 12;

#[cfg(target_arch = "aarch64")]
#[cfg(target_vendor = "apple")]
pub const DEVICE: &str = "ios";
#[cfg(target_arch = "aarch64")]
#[cfg(target_vendor = "unknown")]
pub const DEVICE: &str = "android";
#[cfg(target_arch = "x86_64")]
pub const DEVICE: &str = "web";

use crate::client::Client;
use crate::error::ClientError;
use crate::models::{
    AuthInfo, ChatLog, Content, Conversation, ListChatLogResult, ListConversationResult,
    ListUserResult, Topic, TopicKnock, TopicMember, TopicNotice, User,
};

pub use client::services::login;
pub type Result<T, E = ClientError> = std::result::Result<T, E>;

#[derive(Clone, PartialEq, Default, Debug)]
pub enum NetworkState {
    Connecting,
    Connected,
    #[default]
    Disconnected,
}
pub trait Callback: Send + Sync {
    fn on_connected(&self) {}
    fn on_connecting(&self) {}
    fn on_net_broken(&self, reason: String) {
        debug!("on_net_broken: {}", reason);
    }
    fn on_kickoff_by_other_client(&self, reason: String) {
        debug!("on_kickoff_by_other_client: {}", reason);
    }
    // 发送消息失败
    fn on_send_message_fail(&self, topic_id: String, chat_id: String, code: u32) {
        debug!("on_send_message_fail: {} {} {}", topic_id, chat_id, code);
    }
    // 收到群申请
    fn on_topic_knock(&self, topic_id: String, message: String, source: String) {
        debug!("on_topic_knock: {} {} {}", topic_id, message, source);
    }
    // 收到群申请拒绝
    fn on_topic_knock_reject(&self, user_id: String, message: String) {
        debug!("on_topic_knock_reject: {} {}", user_id, message);
    }
    // 加入一个群聊
    fn on_topic_join(&self, topic_id: String) {
        debug!("on_topic_join: {}", topic_id);
    } // 消息已读
    fn on_read(&self, topic_id: String) {
        debug!("on_read: {}", topic_id);
    }
    // 撤回一条消息
    fn on_recall(&self, topic_id: String, chat_id: String) {
        debug!("on_recall: {} {}", topic_id, chat_id);
    }
    // 正在输入
    fn on_typing(&self, topic_id: String, user_id: String) {
        debug!("on_typing: {} {}", topic_id, user_id);
    }
    // 收到一条消息
    fn on_topic_message(&self, topic_id: String, message: ChatLog) {
        debug!("on_topic_message: {} {:?}", topic_id, message);
    }
    // 群公告更新
    fn on_topic_notice_updated(&self, topic_id: String, notice: TopicNotice) {
        debug!("on_topic_notice_updated: {} {:?}", topic_id, notice);
    }
    // 群成员更新
    fn on_topic_member_updated(&self, topic_id: String, member: User, is_add: bool) {
        debug!(
            "on_topic_member_updated: {} {:?} {}",
            topic_id, member, is_add
        );
    }
    // 会话更新
    fn on_conversation_updated(&self, _conversations: Vec<Conversation>) {
        debug!("on_conversation_updated: {:?}", _conversations);
    }
    // 会话被删除
    fn on_conversation_removed(&self, topic_id: String) {
        debug!("on_conversation_removed: {}", topic_id);
    }
    // 被踢出群, 每个人都会收到, 去掉本地的缓存
    fn on_topic_kickoff(&self, topic_id: String, admin_id: String, user_id: String) {
        debug!("on_topic_kickoff: {} {} {}", topic_id, admin_id, user_id);
    }
    // 群被解散
    fn on_topic_dismissed(&self, topic_id: String, user_id: String) {
        debug!("on_topic_dismissed: {} {}", topic_id, user_id);
    }
    // 群被禁言
    fn on_topic_silent(&self, topic_id: String, duration: String) {
        debug!("on_topic_silent: {} {}", topic_id, duration);
    }
    // 群成员被禁言
    fn on_topic_silent_member(&self, topic_id: String, user_id: String, duration: String) {
        debug!(
            "on_topic_silent_member: {} {} {}",
            topic_id, user_id, duration
        );
    }

    // 下载的进度
    fn on_download_progress(&self, url: String, received: u32, total: u32, key: String) {
        debug!(
            "on_download_progress: {} {} {} {}",
            url, received, total, key
        );
    }
    // 下载结束
    fn on_download_done(&self, url: String, file_name: String, size: u32, key: String) {
        debug!("on_download_done: {} {} {} {}", url, file_name, size, key);
    }
    // 下载取消或者失败
    fn on_download_cancel(&self, url: String, file_name: String, reason: String, key: String) {
        debug!(
            "on_download_cancel: {} {} {} {}",
            url, file_name, reason, key
        );
    }

    // 上传的进度
    fn on_upload_progress(&self, file_name: String, received: u32, total: u32, key: String) {
        debug!(
            "on_upload_progress: {} {} {} {}",
            file_name, received, total, key
        );
    }
    fn on_upload_done(&self, url: String, file_name: String, size: u32, key: String) {
        debug!("on_upload_done: {} {} {} {}", url, file_name, size, key);
    }
    // 上传取消或者失败
    fn on_upload_cancel(&self, url: String, file_name: String, reason: String, key: String) {
        debug!("on_upload_cancel: {} {} {} {}", url, file_name, reason, key);
    }
}

pub trait Uploader: Send + Sync {
    fn upload(&self, local_file_name: String, key: String);
    fn download(&self, file_url: String, save_to: String, key: String);
    fn cancel_download(&self, file_url: String, key: String);
    fn cancel_upload(&self, local_file_name: String, key: String);
}

pub fn init_log(level: String, is_test: bool) {
    let _ = env_logger::builder()
        .is_test(is_test)
        .format(|buf, record| {
            writeln!(
                buf,
                "{} [{}] {}:{} - {}",
                chrono::Local::now().format("%Y-%m-%d %H:%M:%S"),
                record.level(),
                record.file().unwrap_or("unknown"),
                record.line().unwrap_or(0),
                record.args()
            )
        })
        .format_timestamp(None)
        .filter_level(level.parse().unwrap())
        .try_init();
}

pub fn set_current_user(root: String, user_id: String) -> crate::Result<()> {
    let mut root = root;
    if root == String::default() {
        root = String::from(".");
    }
    let current_file = std::path::PathBuf::from(root.clone()).join(".current_user");
    if user_id != String::default() {
        let user_dir = std::path::PathBuf::from(root).join(&user_id);
        std::fs::create_dir_all(std::path::Path::new(&user_dir))?;
    }
    Ok(std::fs::write(&current_file, user_id)?)
}

pub fn get_current_user(root: String) -> Option<AuthInfo> {
    let mut root = root;
    if root == String::default() {
        root = String::from(".");
    }

    let current_file = std::path::PathBuf::from(root.clone()).join(".current_user");
    match std::fs::read_to_string(&current_file) {
        Ok(user_id) => Some(AuthInfo {
            user_id,
            ..Default::default()
        }),
        _ => None,
    }
}

uniffi::include_scaffolding!("client");