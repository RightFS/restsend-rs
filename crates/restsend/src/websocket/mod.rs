use std::time::Duration;

#[cfg(test)]
mod tests;

mod tokio_impl;
#[allow(unused)]
pub trait WebSocketCallback: Send + Sync {
    fn on_connected(&self) {}
    fn on_connecting(&self) {}
    fn on_net_broken(&self, reason: String) {}
    fn on_message(&self, message: String) {}
}

#[derive(Default, Debug, Clone)]
pub struct WebsocketOption {
    pub url: String,
    pub token: String,
    pub handshake_timeout: Duration,
}

pub struct WebSocket {}

impl WebsocketOption {
    pub fn new(url: &str, token: &str) -> Self {
        Self {
            url: url.to_string(),
            token: token.to_string(),
            handshake_timeout: Duration::from_secs(30), // default 30s
        }
    }
}
