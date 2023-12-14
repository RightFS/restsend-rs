use wasm_bindgen::prelude::*;
use wasm_bindgen::JsValue;

/// Signin with userId and password or token
#[allow(non_snake_case)]
#[wasm_bindgen]
pub async fn signin(
    endpoint: String,
    userId: String,
    password: Option<String>,
    token: Option<String>,
) -> Result<JsValue, JsValue> {
    let info = match password {
        Some(password) => {
            restsend_sdk::services::auth::login_with_password(endpoint, userId, password).await
        }
        None => {
            restsend_sdk::services::auth::login_with_token(
                endpoint,
                userId,
                token.unwrap_or_default(),
            )
            .await
        }
    }
    .map_err(|e| JsValue::from_str(e.to_string().as_str()))?;
    serde_wasm_bindgen::to_value(&info).map_err(|e| JsValue::from_str(e.to_string().as_str()))
}
/// Signup with userId and password
#[allow(non_snake_case)]
#[wasm_bindgen]
pub async fn signup(
    endpoint: String,
    userId: String,
    password: String,
) -> Result<JsValue, JsValue> {
    let info = restsend_sdk::services::auth::signup(endpoint, userId, password)
        .await
        .map_err(|e| JsValue::from_str(e.to_string().as_str()))?;
    serde_wasm_bindgen::to_value(&info).map_err(|e| JsValue::from_str(e.to_string().as_str()))
}