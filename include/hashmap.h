#ifndef HASHMAP_H
#define HASHMAP_H

#include <cstdlib>
#include <iostream>
#include <new>
#include <cstring>
#include <type_traits>
#include <functional> // for std::hash
#include "dynamicarray.h"
#include "linkedlist.h"

// Default Key Equal functor using operator==
template <typename T> struct DefaultKeyEqual {
  bool operator()(const T &a, const T &b) const { return a == b; }
};

// Default Hash functor using std::hash for maximum generality
template <typename Key> struct DefaultHash {
  std::size_t operator()(const Key &key) const {
    return std::hash<Key>{}(key);
  }
};

// Streamable helper to check and safely print values/keys to stream in print()
namespace details {
template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, decltype(void(std::declval<std::ostream &>() << std::declval<const T &>()))>
    : std::true_type {};

template <typename T>
typename std::enable_if<is_streamable<T>::value>::type
printValue(std::ostream &os, const T &val) {
  os << val;
}

template <typename T>
typename std::enable_if<!is_streamable<T>::value>::type
printValue(std::ostream &os, const T &) {
  os << "<unstreamable>";
}
} // namespace details

template <typename Key, typename Value> struct KeyValuePair {
  Key key;
  Value value;

  KeyValuePair() = default;
  KeyValuePair(const Key &k, const Value &v) : key(k), value(v) {}

  bool operator==(const KeyValuePair &other) const {
    return key == other.key;
  }
};

template <typename Key, typename Value, typename Hash = DefaultHash<Key>,
          typename KeyEqual = DefaultKeyEqual<Key>>
class HashMap {
private:
  DynamicArray<LinkedList<KeyValuePair<Key, Value>>> buckets;
  int bucketCount;
  int elementCount;
  float maxLoadFactor;
  Hash hashFn;
  KeyEqual equalFn;

  int getBucketIndex(const Key &key) const;
  void rehash(int newCapacity);

public:
  // Constructors & Destructor (Rule of Zero / Defaulted Rule of Three)
  HashMap(int initialCapacity = 16);
  ~HashMap() = default;
  HashMap(const HashMap &other) = default;
  HashMap &operator=(const HashMap &other) = default;

  // Core Operations
  void insert(const Key &key, const Value &value);
  bool get(const Key &key, Value &value) const;
  bool remove(const Key &key);
  bool contains(const Key &key) const;
  int size() const;
  bool isEmpty() const;
  float loadFactor() const;
  void clear();
  void print() const;
};

#include "../src/hashmap.tpp" 

#endif // HASHMAP_H
