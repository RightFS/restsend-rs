/* tslint:disable */
/* eslint-disable */
export const memory: WebAssembly.Memory;
export function client_set_onconnected(a: number, b: number): void;
export function client_set_onconnecting(a: number, b: number): void;
export function client_set_ontokenexpired(a: number, b: number): void;
export function client_set_onbroken(a: number, b: number): void;
export function client_set_onkickoff(a: number, b: number): void;
export function client_set_onsystemrequest(a: number, b: number): void;
export function client_set_onunknownrequest(a: number, b: number): void;
export function client_set_ontopictyping(a: number, b: number): void;
export function client_set_ontopicmessage(a: number, b: number): void;
export function client_set_ontopicread(a: number, b: number): void;
export function client_set_onconversationsupdated(a: number, b: number): void;
export function client_set_onconversationsremoved(a: number, b: number): void;
export function setLogging(a: number, b: number): void;
export function client_doSend(a: number, b: number, c: number, d: number, e: number): number;
export function client_doTyping(a: number, b: number, c: number): number;
export function client_doRecall(a: number, b: number, c: number, d: number, e: number, f: number): number;
export function client_doSendVoice(a: number, b: number, c: number, d: number, e: number): number;
export function client_doSendVideo(a: number, b: number, c: number, d: number, e: number): number;
export function client_doSendFile(a: number, b: number, c: number, d: number, e: number): number;
export function client_doSendLocation(a: number, b: number, c: number, d: number, e: number, f: number, g: number, h: number, i: number, j: number): number;
export function client_doSendLink(a: number, b: number, c: number, d: number, e: number, f: number): number;
export function client_doSendLogs(a: number, b: number, c: number, d: number, e: number, f: number, g: number, h: number): number;
export function client_doSendText(a: number, b: number, c: number, d: number, e: number, f: number): number;
export function client_doSendImage(a: number, b: number, c: number, d: number, e: number): number;
export function client_doUpdateExtra(a: number, b: number, c: number, d: number, e: number, f: number, g: number): number;
export function __wbg_client_free(a: number): void;
export function client_new(a: number, b: number, c: number): number;
export function client_connectionStatus(a: number, b: number): void;
export function client_shutdown(a: number): number;
export function client_connect(a: number): number;
export function client_createTopic(a: number, b: number, c: number, d: number, e: number, f: number, g: number): number;
export function client_joinTopic(a: number, b: number, c: number, d: number, e: number, f: number, g: number): number;
export function client_addMember(a: number, b: number, c: number, d: number, e: number): number;
export function client_getTopic(a: number, b: number, c: number): number;
export function client_getTopicAdmins(a: number, b: number, c: number): number;
export function client_getTopicOwner(a: number, b: number, c: number): number;
export function client_getTopicMembers(a: number, b: number, c: number, d: number, e: number, f: number): number;
export function client_getTopicKnocks(a: number, b: number, c: number): number;
export function client_updateTopic(a: number, b: number, c: number, d: number): number;
export function client_updateTopicNotice(a: number, b: number, c: number, d: number, e: number): number;
export function client_silentTopic(a: number, b: number, c: number, d: number, e: number): number;
export function client_silentTopicMember(a: number, b: number, c: number, d: number, e: number, f: number, g: number): number;
export function client_addTopicAdmin(a: number, b: number, c: number, d: number, e: number): number;
export function client_removeTopicAdmin(a: number, b: number, c: number, d: number, e: number): number;
export function client_transferTopic(a: number, b: number, c: number, d: number, e: number): number;
export function client_quitTopic(a: number, b: number, c: number): number;
export function client_dismissTopic(a: number, b: number, c: number): number;
export function client_acceptTopicJoin(a: number, b: number, c: number, d: number, e: number, f: number, g: number): number;
export function client_declineTopicJoin(a: number, b: number, c: number, d: number, e: number, f: number, g: number): number;
export function client_removeTopicMember(a: number, b: number, c: number, d: number, e: number): number;
export function signin(a: number, b: number, c: number, d: number, e: number, f: number, g: number, h: number): number;
export function signup(a: number, b: number, c: number, d: number, e: number, f: number): number;
export function logout(a: number, b: number, c: number, d: number): number;
export function client_createChat(a: number, b: number, c: number): number;
export function client_cleanMessages(a: number, b: number, c: number): number;
export function client_removeMessages(a: number, b: number, c: number, d: number, e: number): number;
export function client_syncChatLogs(a: number, b: number, c: number, d: number, e: number, f: number): number;
export function client_syncConversations(a: number, b: number): number;
export function client_getConversation(a: number, b: number, c: number, d: number): number;
export function client_removeConversation(a: number, b: number, c: number): number;
export function client_setConversationRemark(a: number, b: number, c: number, d: number, e: number): number;
export function client_setConversationSticky(a: number, b: number, c: number, d: number): number;
export function client_setConversationMute(a: number, b: number, c: number, d: number): number;
export function client_setConversationRead(a: number, b: number, c: number): number;
export function client_setConversationTags(a: number, b: number, c: number, d: number): number;
export function client_setConversationExtra(a: number, b: number, c: number, d: number): number;
export function client_filterConversation(a: number, b: number): number;
export function client_getUser(a: number, b: number, c: number, d: number): number;
export function client_getUsers(a: number, b: number, c: number): number;
export function client_setUserRemark(a: number, b: number, c: number, d: number, e: number): number;
export function client_setUserStar(a: number, b: number, c: number, d: number): number;
export function client_setUserBlock(a: number, b: number, c: number, d: number): number;
export function client_setAllowGuestChat(a: number, b: number): number;
export function __wbg_intounderlyingsink_free(a: number): void;
export function intounderlyingsink_write(a: number, b: number): number;
export function intounderlyingsink_close(a: number): number;
export function intounderlyingsink_abort(a: number, b: number): number;
export function __wbg_intounderlyingbytesource_free(a: number): void;
export function intounderlyingbytesource_type(a: number, b: number): void;
export function intounderlyingbytesource_autoAllocateChunkSize(a: number): number;
export function intounderlyingbytesource_start(a: number, b: number): void;
export function intounderlyingbytesource_pull(a: number, b: number): number;
export function intounderlyingbytesource_cancel(a: number): void;
export function __wbg_intounderlyingsource_free(a: number): void;
export function intounderlyingsource_pull(a: number, b: number): number;
export function intounderlyingsource_cancel(a: number): void;
export function __wbg_readablestreamgetreaderoptions_free(a: number): void;
export function readablestreamgetreaderoptions_mode(a: number): number;
export function __wbg_pipeoptions_free(a: number): void;
export function pipeoptions_preventClose(a: number): number;
export function pipeoptions_preventCancel(a: number): number;
export function pipeoptions_preventAbort(a: number): number;
export function pipeoptions_signal(a: number): number;
export function __wbg_queuingstrategy_free(a: number): void;
export function queuingstrategy_highWaterMark(a: number): number;
export function __wbindgen_malloc(a: number, b: number): number;
export function __wbindgen_realloc(a: number, b: number, c: number, d: number): number;
export const __wbindgen_export_2: WebAssembly.Table;
export function wasm_bindgen__convert__closures__invoke0_mut__h87d9a45b9cadb27e(a: number, b: number): void;
export function wasm_bindgen__convert__closures__invoke1_mut__h59613db93b1ce681(a: number, b: number, c: number): void;
export function wasm_bindgen__convert__closures__invoke1_mut__he4d116b84973670a(a: number, b: number, c: number): void;
export function __wbindgen_add_to_stack_pointer(a: number): number;
export function __wbindgen_free(a: number, b: number, c: number): void;
export function __wbindgen_exn_store(a: number): void;
export function wasm_bindgen__convert__closures__invoke2_mut__h26de80423724072a(a: number, b: number, c: number, d: number): void;
