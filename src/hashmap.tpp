#ifndef HASHMAP_TPP
#define HASHMAP_TPP

#ifndef HASHMAP_H
#include "../include/hashmap.h"
#endif

// HashMap Implementation
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::HashMap(int initialCapacity)
    : bucketCount(initialCapacity <= 0 ? 16 : initialCapacity), elementCount(0),
      maxLoadFactor(0.75f) {
  for (int i = 0; i < bucketCount; ++i) {
    buckets.append(LinkedList<KeyValuePair<Key, Value>>());
  }
}

// Private helper to compute bucket index
template <typename Key, typename Value, typename Hash, typename KeyEqual>
int HashMap<Key, Value, Hash, KeyEqual>::getBucketIndex(const Key &key) const {
  return static_cast<int>(hashFn(key) % static_cast<size_t>(bucketCount));
}

// Private helper to rehash and resize the HashMap buckets array
template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::rehash(int newCapacity) {
  DynamicArray<LinkedList<KeyValuePair<Key, Value>>> newBuckets;
  for (int i = 0; i < newCapacity; ++i) {
    newBuckets.append(LinkedList<KeyValuePair<Key, Value>>());
  }

  int oldCapacity = bucketCount;
  bucketCount = newCapacity;

  for (int i = 0; i < oldCapacity; ++i) {
    const LinkedList<KeyValuePair<Key, Value>> &bucket = buckets.get(i);
    for (int j = 0; j < bucket.size(); ++j) {
      const KeyValuePair<Key, Value> &pair = bucket.get(j);
      int newIndex = getBucketIndex(pair.key);
      newBuckets.get(newIndex).insertFront(pair);
    }
  }

  buckets = newBuckets;
}

// Public insert operation
template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::insert(const Key &key,
                                                 const Value &value) {
  // Check load factor and resize if necessary
  if (elementCount + 1 > bucketCount * maxLoadFactor) {
    rehash(bucketCount * 2);
  }

  int index = getBucketIndex(key);
  LinkedList<KeyValuePair<Key, Value>> &bucket = buckets.get(index);

  for (int i = 0; i < bucket.size(); ++i) {
    KeyValuePair<Key, Value> &pair = bucket.get(i);
    if (equalFn(pair.key, key)) {
      pair.value = value;
      return;
    }
  }

  // Key doesn't exist, insert new node at front
  bucket.insertFront(KeyValuePair<Key, Value>(key, value));
  elementCount++;
}

// Public get operation
template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashMap<Key, Value, Hash, KeyEqual>::get(const Key &key,
                                              Value &value) const {
  int index = getBucketIndex(key);
  const LinkedList<KeyValuePair<Key, Value>> &bucket = buckets.get(index);
  for (int i = 0; i < bucket.size(); ++i) {
    const KeyValuePair<Key, Value> &pair = bucket.get(i);
    if (equalFn(pair.key, key)) {
      value = pair.value;
      return true;
    }
  }
  return false;
}

// Public remove operation
template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashMap<Key, Value, Hash, KeyEqual>::remove(const Key &key) {
  int index = getBucketIndex(key);
  LinkedList<KeyValuePair<Key, Value>> &bucket = buckets.get(index);
  for (int i = 0; i < bucket.size(); ++i) {
    const KeyValuePair<Key, Value> &pair = bucket.get(i);
    if (equalFn(pair.key, key)) {
      bucket.deleteAt(i);
      elementCount--;
      return true;
    }
  }
  return false;
}

// Public contains operation
template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashMap<Key, Value, Hash, KeyEqual>::contains(const Key &key) const {
  int index = getBucketIndex(key);
  const LinkedList<KeyValuePair<Key, Value>> &bucket = buckets.get(index);
  for (int i = 0; i < bucket.size(); ++i) {
    const KeyValuePair<Key, Value> &pair = bucket.get(i);
    if (equalFn(pair.key, key)) {
      return true;
    }
  }
  return false;
}

// Public size query
template <typename Key, typename Value, typename Hash, typename KeyEqual>
int HashMap<Key, Value, Hash, KeyEqual>::size() const {
  return elementCount;
}

// Public isEmpty query
template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool HashMap<Key, Value, Hash, KeyEqual>::isEmpty() const {
  return elementCount == 0;
}

// Public loadFactor query
template <typename Key, typename Value, typename Hash, typename KeyEqual>
float HashMap<Key, Value, Hash, KeyEqual>::loadFactor() const {
  if (bucketCount == 0)
    return 0.0f;
  return static_cast<float>(elementCount) / bucketCount;
}

// Private/Public helper to clear all elements from HashMap
template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::clear() {
  for (int i = 0; i < bucketCount; ++i) {
    buckets.get(i).clear();
  }
  elementCount = 0;
}

// Public print operation
template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::print() const {
  for (int i = 0; i < bucketCount; ++i) {
    std::cout << "Bucket " << i << ": ";
    const LinkedList<KeyValuePair<Key, Value>> &bucket = buckets.get(i);
    for (int j = 0; j < bucket.size(); ++j) {
      const KeyValuePair<Key, Value> &pair = bucket.get(j);
      std::cout << "[";
      details::printValue(std::cout, pair.key);
      std::cout << ": ";
      details::printValue(std::cout, pair.value);
      std::cout << "] -> ";
    }
    std::cout << "nullptr" << std::endl;
  }
}

#endif // HASHMAP_TPP
