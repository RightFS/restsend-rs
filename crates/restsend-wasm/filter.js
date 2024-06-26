/*
    * filterConversations
    * Retrieve conversations from the indexedDB table that satisfy the predicate function and are not cancelled
    * @param {string} name - the name of the table
    * @param {function} predicate - a function that takes a conversation and returns a boolean
    * @param {function} isCancelled - a function that returns a boolean
    * @param {number} updatedAt - the timestamp of the last conversation to retrieve
    * @param {number} limit - the maximum number of conversations to retrieve
*/
export async function filterConversations(name,
    predicate,
    isCancelled,
    updatedAt,
    limit = 200
) {
    const version = 1
    const request = window.indexedDB.open(name, version)

    return new Promise((resolve, reject) => {
        request.onerror = (event) => {
            reject(event)
        }
        request.onsuccess = (event) => {
            var db = request.result
            const objectStore = db
                .transaction(name, "readonly")
                .objectStore(name)

            const index = objectStore.index('partition+sortkey')
            let range = undefined
            if (updatedAt !== undefined) {
                const timestamp = new Date(updatedAt).getTime()
                range = IDBKeyRange.bound(['', Infinity], ['', timestamp], false, true)
            }

            const cursor = index.openCursor(range, direction = 'prev')
            let items = []
            cursor.onsuccess = (event) => {
                const cursor = event.target.result
                if (!cursor || (isCancelled != undefined && isCancelled()) || (limit !== undefined && items.length >= limit)) {
                    db.close()
                    resolve(items)
                    return
                }
                const value = JSON.parse(cursor.value.value)
                if (predicate != undefined && !predicate(value)) {
                    cursor.continue()
                    return
                }
                items.push(value)
                cursor.continue()
                return
            }
            cursor.onerror = (event) => {
                reject(event)
            };
        }
    });
}