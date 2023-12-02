use crate::{
    error::ClientError::{Forbidden, HTTPError, InvalidPassword},
    USER_AGENT,
};
use anyhow::Result;
use log::{info, warn};
use reqwest::{
    header::{HeaderValue, AUTHORIZATION, CONTENT_TYPE},
    RequestBuilder, Response,
};
use std::time::Duration;

pub mod auth;
pub mod conversation;
pub mod media;
pub mod response;
#[cfg(test)]
mod tests;
pub mod topic;
pub mod topic_admin;
pub mod user;

const MEDIA_TIMEOUT_SECS: u64 = 300; // 5 minutes
const API_TIMEOUT_SECS: u64 = 60; // 1 minute
const API_PREFIX: &str = "/api";
const LOGS_LIMIT: u32 = 100;
const USERS_LIMIT: u32 = 100;

pub(super) fn make_get_request(
    endpoint: &str,
    uri: &str,
    auth_token: Option<String>,
    timeout: Option<Duration>,
) -> RequestBuilder {
    let url = format!("{}{}", endpoint, uri);
    let req = reqwest::ClientBuilder::new()
        .user_agent(USER_AGENT)
        .build()
        .unwrap()
        .get(&url)
        .header(
            CONTENT_TYPE,
            HeaderValue::from_bytes(b"application/json").unwrap(),
        )
        .timeout(timeout.unwrap_or(Duration::from_secs(API_TIMEOUT_SECS)));

    match auth_token {
        Some(token) => req.header(AUTHORIZATION, HeaderValue::from_str(&token).unwrap()),
        None => req,
    }
}

pub(super) fn make_post_request(
    endpoint: &str,
    uri: &str,
    auth_token: Option<&str>,
    content_type: Option<&str>,
    body: Option<String>,
    timeout: Option<Duration>,
) -> RequestBuilder {
    let url = format!("{}{}", endpoint, uri);
    let req = reqwest::ClientBuilder::new()
        .user_agent(USER_AGENT)
        .build()
        .unwrap()
        .post(&url)
        .timeout(timeout.unwrap_or(Duration::from_secs(API_TIMEOUT_SECS)));

    let req = match content_type {
        Some(content_type) => req.header(
            CONTENT_TYPE,
            HeaderValue::from_bytes(content_type.as_bytes()).unwrap(),
        ),
        None => req,
    };

    let req = match auth_token {
        Some(token) => req.header(AUTHORIZATION, HeaderValue::from_str(&token).unwrap()),
        None => req,
    };
    match body {
        Some(body) => req.body(body),
        None => req,
    }
}

pub(crate) async fn handle_response<T>(resp: Response) -> Result<T>
where
    T: serde::de::DeserializeOwned,
{
    let status = resp.status();
    let url = resp.url().to_string();

    match status {
        reqwest::StatusCode::OK => Ok(resp.json::<T>().await?),
        _ => {
            let body = resp.text().await?;
            let msg = serde_json::from_str::<serde_json::Value>(&body)
                .map(|v| {
                    let msg = v["error"].as_str().unwrap_or_default();
                    msg.to_string()
                })
                .unwrap_or(status.to_string());

            warn!("response with {} error: {}", url, msg);

            match status {
                reqwest::StatusCode::FORBIDDEN => Err(Forbidden(msg.to_string()).into()),
                reqwest::StatusCode::UNAUTHORIZED => Err(InvalidPassword(msg.to_string()).into()),
                reqwest::StatusCode::BAD_REQUEST => Err(HTTPError(msg.to_string()).into()),
                _ => Err(HTTPError(msg.to_string()).into()),
            }
        }
    }
}

pub(super) async fn api_call<R>(
    endpoint: &str,
    uri: &str,
    auth_token: &str,
    body: Option<String>,
) -> Result<R>
where
    R: serde::de::DeserializeOwned,
{
    let st = tokio::time::Instant::now();
    let req = make_post_request(
        endpoint,
        &format!("{}{}", API_PREFIX, uri),
        Some(auth_token),
        Some("application/json"),
        body,
        None,
    );

    let resp = req.send().await.map_err(|e| HTTPError(e.to_string()))?;
    let status = resp.status();

    info!(
        "api url:{}{} status:{} usage: {:?}",
        endpoint,
        uri,
        status,
        st.elapsed()
    );
    handle_response::<R>(resp).await
}