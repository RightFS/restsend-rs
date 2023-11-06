// This file was autogenerated by some hot garbage in the `uniffi` crate.
// Trust me, you don't want to mess with it!

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// The following structs are used to implement the lowest level
// of the FFI, and thus useful to multiple uniffied crates.
// We ensure they are declared exactly once, with a header guard, UNIFFI_SHARED_H.
#ifdef UNIFFI_SHARED_H
    // We also try to prevent mixing versions of shared uniffi header structs.
    // If you add anything to the #else block, you must increment the version suffix in UNIFFI_SHARED_HEADER_V4
    #ifndef UNIFFI_SHARED_HEADER_V4
        #error Combining helper code from multiple versions of uniffi is not supported
    #endif // ndef UNIFFI_SHARED_HEADER_V4
#else
#define UNIFFI_SHARED_H
#define UNIFFI_SHARED_HEADER_V4
// ⚠️ Attention: If you change this #else block (ending in `#endif // def UNIFFI_SHARED_H`) you *must* ⚠️
// ⚠️ increment the version suffix in all instances of UNIFFI_SHARED_HEADER_V4 in this file.           ⚠️

typedef struct RustBuffer
{
    int32_t capacity;
    int32_t len;
    uint8_t *_Nullable data;
} RustBuffer;

typedef int32_t (*ForeignCallback)(uint64_t, int32_t, const uint8_t *_Nonnull, int32_t, RustBuffer *_Nonnull);

// Task defined in Rust that Swift executes
typedef void (*UniFfiRustTaskCallback)(const void * _Nullable);

// Callback to execute Rust tasks using a Swift Task
//
// Args:
//   executor: ForeignExecutor lowered into a size_t value
//   delay: Delay in MS
//   task: UniFfiRustTaskCallback to call
//   task_data: data to pass the task callback
typedef void (*UniFfiForeignExecutorCallback)(size_t, uint32_t, UniFfiRustTaskCallback _Nullable, const void * _Nullable);

typedef struct ForeignBytes
{
    int32_t len;
    const uint8_t *_Nullable data;
} ForeignBytes;

// Error definitions
typedef struct RustCallStatus {
    int8_t code;
    RustBuffer errorBuf;
} RustCallStatus;

// ⚠️ Attention: If you change this #else block (ending in `#endif // def UNIFFI_SHARED_H`) you *must* ⚠️
// ⚠️ increment the version suffix in all instances of UNIFFI_SHARED_HEADER_V4 in this file.           ⚠️
#endif // def UNIFFI_SHARED_H

// Callbacks for UniFFI Futures
typedef void (*UniFfiFutureCallbackUInt8)(const void * _Nonnull, uint8_t, RustCallStatus);
typedef void (*UniFfiFutureCallbackUInt32)(const void * _Nonnull, uint32_t, RustCallStatus);
typedef void (*UniFfiFutureCallbackUnsafeMutableRawPointer)(const void * _Nonnull, void*_Nonnull, RustCallStatus);
typedef void (*UniFfiFutureCallbackRustBuffer)(const void * _Nonnull, RustBuffer, RustCallStatus);

// Scaffolding functions
void uniffi_client_fn_free_client(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void*_Nonnull uniffi_client_fn_constructor_client_new(RustBuffer db_name, RustBuffer endpoint, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_callback(void*_Nonnull ptr, RustBuffer callback, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_uploader(void*_Nonnull ptr, RustBuffer uploader, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_prepare(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_attach(void*_Nonnull ptr, RustBuffer info, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_app_active(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_app_deactivate(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_logout(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_run_loop(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_shutdown(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_network_state(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
uint32_t uniffi_client_fn_method_client_get_topics_knock_count(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
uint32_t uniffi_client_fn_method_client_get_conversations_count(void*_Nonnull ptr, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_conversation(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_remove_conversation(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_conversation_sticky(void*_Nonnull ptr, RustBuffer topic_id, int8_t sticky, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_conversation_mute(void*_Nonnull ptr, RustBuffer topic_id, int8_t mute, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_conversation_read(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_conversations(void*_Nonnull ptr, RustBuffer updated_at, uint32_t limit, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_sync_conversations(void*_Nonnull ptr, int8_t without_cache, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_topic(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_topic_admins(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_topic_owner(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_topic_members(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer updated_at, uint32_t limit, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_chat_logs_desc(void*_Nonnull ptr, RustBuffer topic_id, uint64_t start_seq, uint64_t end_seq, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_chat_log(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_search_chat_log(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer sender_id, RustBuffer keyword, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_topic_knocks(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_create_topic(void*_Nonnull ptr, RustBuffer name, RustBuffer icon, RustBuffer members, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_create_chat(void*_Nonnull ptr, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_update_topic(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer name, RustBuffer icon, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_update_topic_notice(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer text, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_silent_topic(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer duration, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_silent_topic_member(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustBuffer duration, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_add_topic_admin(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_remove_topic_admin(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_transfer_topic(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_quit_topic(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_dismiss_topic(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_join_topic(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer source, RustBuffer message, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_accept_topic_join(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustBuffer memo, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_decline_topic_join(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustBuffer message, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_invite_topic_member(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_remove_topic_member(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_clean_topic_history(void*_Nonnull ptr, RustBuffer topic_id, int8_t sync, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_remove_messages(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer chat_ids, int8_t sync, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_get_user(void*_Nonnull ptr, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_user_remark(void*_Nonnull ptr, RustBuffer user_id, RustBuffer remark, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_user_star(void*_Nonnull ptr, RustBuffer user_id, int8_t star, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_user_block(void*_Nonnull ptr, RustBuffer user_id, int8_t block, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_set_allow_guest_chat(void*_Nonnull ptr, int8_t allow, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_typing(void*_Nonnull ptr, RustBuffer topic_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_recall(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer chat_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_text(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer text, RustBuffer mentions, RustBuffer reply_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_image(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer url_or_data, RustBuffer mentions, RustBuffer reply_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_voice(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer url_or_data, RustBuffer duration, RustBuffer mentions, RustBuffer reply_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_video(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer url, RustBuffer thumbnail, RustBuffer duration, RustBuffer mentions, RustBuffer reply_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_file(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer url_or_data, RustBuffer filename, uint64_t size, RustBuffer mentions, RustBuffer reply_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_location(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer latitude, RustBuffer longitude, RustBuffer address, RustBuffer mentions, RustBuffer reply_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_link(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer url, RustBuffer mentions, RustBuffer reply_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send_invite(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer mentions, RustBuffer message, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_method_client_do_send(void*_Nonnull ptr, RustBuffer topic_id, RustBuffer content, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_upload(void*_Nonnull ptr, RustBuffer uploader_url, RustBuffer local_file_path, RustBuffer key, int8_t is_private, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_download(void*_Nonnull ptr, RustBuffer file_url, RustBuffer save_to, RustBuffer key, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_cancel_download(void*_Nonnull ptr, RustBuffer file_url, RustBuffer key, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_method_client_cancel_upload(void*_Nonnull ptr, RustBuffer local_file_path, RustBuffer key, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_init_callback_callback(ForeignCallback _Nonnull callback_stub, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_init_callback_uploader(ForeignCallback _Nonnull callback_stub, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_func_init_log(RustBuffer level, int8_t is_test, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_func_get_current_user(RustBuffer root, RustCallStatus *_Nonnull out_status
);
void uniffi_client_fn_func_set_current_user(RustBuffer root, RustBuffer user_id, RustCallStatus *_Nonnull out_status
);
RustBuffer uniffi_client_fn_func_login(RustBuffer endpoint, RustBuffer email, RustBuffer password, RustCallStatus *_Nonnull out_status
);
RustBuffer ffi_client_rustbuffer_alloc(int32_t size, RustCallStatus *_Nonnull out_status
);
RustBuffer ffi_client_rustbuffer_from_bytes(ForeignBytes bytes, RustCallStatus *_Nonnull out_status
);
void ffi_client_rustbuffer_free(RustBuffer buf, RustCallStatus *_Nonnull out_status
);
RustBuffer ffi_client_rustbuffer_reserve(RustBuffer buf, int32_t additional, RustCallStatus *_Nonnull out_status
);
uint16_t uniffi_client_checksum_func_init_log(void
    
);
uint16_t uniffi_client_checksum_func_get_current_user(void
    
);
uint16_t uniffi_client_checksum_func_set_current_user(void
    
);
uint16_t uniffi_client_checksum_func_login(void
    
);
uint16_t uniffi_client_checksum_method_client_set_callback(void
    
);
uint16_t uniffi_client_checksum_method_client_set_uploader(void
    
);
uint16_t uniffi_client_checksum_method_client_prepare(void
    
);
uint16_t uniffi_client_checksum_method_client_attach(void
    
);
uint16_t uniffi_client_checksum_method_client_app_active(void
    
);
uint16_t uniffi_client_checksum_method_client_app_deactivate(void
    
);
uint16_t uniffi_client_checksum_method_client_logout(void
    
);
uint16_t uniffi_client_checksum_method_client_run_loop(void
    
);
uint16_t uniffi_client_checksum_method_client_shutdown(void
    
);
uint16_t uniffi_client_checksum_method_client_get_network_state(void
    
);
uint16_t uniffi_client_checksum_method_client_get_topics_knock_count(void
    
);
uint16_t uniffi_client_checksum_method_client_get_conversations_count(void
    
);
uint16_t uniffi_client_checksum_method_client_get_conversation(void
    
);
uint16_t uniffi_client_checksum_method_client_remove_conversation(void
    
);
uint16_t uniffi_client_checksum_method_client_set_conversation_sticky(void
    
);
uint16_t uniffi_client_checksum_method_client_set_conversation_mute(void
    
);
uint16_t uniffi_client_checksum_method_client_set_conversation_read(void
    
);
uint16_t uniffi_client_checksum_method_client_get_conversations(void
    
);
uint16_t uniffi_client_checksum_method_client_sync_conversations(void
    
);
uint16_t uniffi_client_checksum_method_client_get_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_get_topic_admins(void
    
);
uint16_t uniffi_client_checksum_method_client_get_topic_owner(void
    
);
uint16_t uniffi_client_checksum_method_client_get_topic_members(void
    
);
uint16_t uniffi_client_checksum_method_client_get_chat_logs_desc(void
    
);
uint16_t uniffi_client_checksum_method_client_get_chat_log(void
    
);
uint16_t uniffi_client_checksum_method_client_search_chat_log(void
    
);
uint16_t uniffi_client_checksum_method_client_get_topic_knocks(void
    
);
uint16_t uniffi_client_checksum_method_client_create_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_create_chat(void
    
);
uint16_t uniffi_client_checksum_method_client_update_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_update_topic_notice(void
    
);
uint16_t uniffi_client_checksum_method_client_silent_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_silent_topic_member(void
    
);
uint16_t uniffi_client_checksum_method_client_add_topic_admin(void
    
);
uint16_t uniffi_client_checksum_method_client_remove_topic_admin(void
    
);
uint16_t uniffi_client_checksum_method_client_transfer_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_quit_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_dismiss_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_join_topic(void
    
);
uint16_t uniffi_client_checksum_method_client_accept_topic_join(void
    
);
uint16_t uniffi_client_checksum_method_client_decline_topic_join(void
    
);
uint16_t uniffi_client_checksum_method_client_invite_topic_member(void
    
);
uint16_t uniffi_client_checksum_method_client_remove_topic_member(void
    
);
uint16_t uniffi_client_checksum_method_client_clean_topic_history(void
    
);
uint16_t uniffi_client_checksum_method_client_remove_messages(void
    
);
uint16_t uniffi_client_checksum_method_client_get_user(void
    
);
uint16_t uniffi_client_checksum_method_client_set_user_remark(void
    
);
uint16_t uniffi_client_checksum_method_client_set_user_star(void
    
);
uint16_t uniffi_client_checksum_method_client_set_user_block(void
    
);
uint16_t uniffi_client_checksum_method_client_set_allow_guest_chat(void
    
);
uint16_t uniffi_client_checksum_method_client_do_typing(void
    
);
uint16_t uniffi_client_checksum_method_client_do_recall(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_text(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_image(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_voice(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_video(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_file(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_location(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_link(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send_invite(void
    
);
uint16_t uniffi_client_checksum_method_client_do_send(void
    
);
uint16_t uniffi_client_checksum_method_client_upload(void
    
);
uint16_t uniffi_client_checksum_method_client_download(void
    
);
uint16_t uniffi_client_checksum_method_client_cancel_download(void
    
);
uint16_t uniffi_client_checksum_method_client_cancel_upload(void
    
);
uint16_t uniffi_client_checksum_constructor_client_new(void
    
);
uint32_t ffi_client_uniffi_contract_version(void
    
);

