use crate::Result;
use async_trait::async_trait;
use std::str::FromStr;

#[allow(unused)]
mod indexeddb;

#[allow(unused)]
mod memory;

#[cfg(not(target_family = "wasm"))]
mod sqlite;

pub trait StoreModel: ToString + FromStr + Sync + Send {
    fn sort_key(&self) -> i64;
}
#[derive(Debug)]
pub struct QueryOption {
    pub keyword: Option<String>,
    pub start_sort_value: Option<i64>,
    pub limit: u32,
}
#[derive(Debug)]
pub struct QueryResult<T: StoreModel> {
    pub start_sort_value: i64,
    pub end_sort_value: i64,
    pub items: Vec<T>,
}

#[cfg(not(feature = "indexeddb"))]
#[cfg(target_family = "wasm")]
pub type Storage = memory::InMemoryStorage;

#[cfg(not(target_family = "wasm"))]
pub type Storage = sqlite::SqliteStorage;

#[cfg(feature = "indexeddb")]
pub type Storage = indexeddb::IndexeddbStorage;

#[async_trait]
pub trait Table<T: StoreModel>: Send + Sync {
    async fn filter(
        &self,
        partition: &str,
        predicate: Box<dyn Fn(T) -> Option<T> + Send>,
    ) -> Option<Vec<T>>;
    async fn query(&self, partition: &str, option: &QueryOption) -> Option<QueryResult<T>>;
    async fn get(&self, partition: &str, key: &str) -> Option<T>;
    async fn set(&self, partition: &str, key: &str, value: Option<&T>) -> Result<()>;
    async fn remove(&self, partition: &str, key: &str) -> Result<()>;
    async fn last(&self, partition: &str) -> Option<T>;
    async fn clear(&self) -> Result<()>;
}

pub(super) fn table_name<T>() -> String {
    let full_name = std::any::type_name::<T>();
    let parts: Vec<&str> = full_name.split("::").collect();
    match parts.last() {
        Some(v) => v,
        None => full_name,
    }
    .into()
}
