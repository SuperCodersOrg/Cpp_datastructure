# Phase 0 – HashMap Design Proposal

**Project:** Collections Library (C++)  
**Component:** HashMap  
**Phase:** 0 – Design Proposal  
**Version:** 1.0

---

# Objective

The objective of designing the HashMap is to build a reusable, dynamically allocated associative container capable of storing key-value pairs while providing fast average-case lookup, insertion, and deletion.

Unlike linear data structures such as arrays and linked lists, the HashMap uses a hash function to map keys into buckets, allowing data to be accessed in approximately constant time.

This implementation focuses on understanding hashing algorithms, collision handling, bucket management, dynamic resizing (rehashing), manual memory management, object ownership, and efficient key-value storage.

The HashMap will serve as the third core component of the Collections Library and later become the storage engine powering the Redis Lite application.

---

# Section 1 – Public API

## Overview

The HashMap stores unique keys associated with values. Every public operation has been selected to satisfy the project requirements while keeping the interface simple, reusable, and extensible.

---

## Proposed Public Interface

```cpp
template <typename Key, typename Value>
class HashMap
{
public:

    // Constructor
    HashMap();

    // Destructor
    ~HashMap();

    // Rule of Three
    HashMap(const HashMap<Key, Value>& other);
    HashMap<Key, Value>& operator=(const HashMap<Key, Value>& other);

    // Insertion / Update
    void set(const Key& key, const Value& value);

    // Retrieval
    Value get(const Key& key) const;

    // Removal
    void remove(const Key& key);

    // Search
    bool contains(const Key& key) const;

    // Utility
    bool isEmpty() const;
    int size() const;
    float loadFactor() const;
    void clear();
    void print() const;
};
```

---

# Section 2 – Internal Representation

## Selected Design

After evaluating multiple collision handling strategies, the proposed implementation will use

**Separate Chaining**

where every bucket stores a linked list of key-value pairs.

Reasons include

- Simple implementation
- Easy collision handling
- Supports dynamic growth
- Easy deletion
- Reuses the previously implemented Linked List
- Easier debugging than probing techniques

---

## Memory Management Policy

The HashMap separates memory allocation from object construction.

Raw memory is allocated using the C Standard Library functions malloc() and released using free().

Since the HashMap is implemented as a template and must support both primitive and user-defined types, objects are constructed using placement new and explicitly destroyed by invoking their destructors before releasing memory.

This design provides manual control over memory while ensuring that constructors and destructors execute correctly.

---

## Entry Structure

```cpp
template <typename Key, typename Value>
class HashNode
{
public:

    Key key;

    Value value;

    HashNode<Key, Value>* next;

    HashNode(const Key& key,
             const Value& value);

    ~HashNode() = default; // It tells the compiler generated destructor is sufficient
};
```

Each node stores

- Key
- Value
- Pointer to the next node in the collision chain

---

## HashMap Data Members

```cpp
template <typename Key, typename Value>
class HashMap
{
private:

    HashNode<Key, Value>** buckets;

    int bucketCount;

    int elementCount;

    float maxLoadFactor;
};
```

---

## Memory Layout

**Diagram**

![Memory Diagram](./hashmapmemorydiagram.png)

---

## Collision Handling

The HashMap will use

**Separate Chaining**

When two different keys produce the same bucket index,

both key-value pairs are stored inside the linked list of that bucket.

Example

```
Bucket 0 → nullptr

Bucket 1
↓

[key1,value1] → [key2,value2] → [key3,value3] → nullptr

Bucket 2 → nullptr

Bucket 3
↓

[key4,value4] → nullptr
```

---

## Hash Function

A deterministic hash function converts every key into an integer hash value.

The hash value is then transformed into a valid bucket index using

bucketIndex = hash(key) % bucketCount;

Key Requirements

For a key type to be stored inside the HashMap, it must support:

Hash computation.

Equality comparison.

Hash computation determines the bucket where a key should be stored.

Equality comparison is used to distinguish between different keys that map to the same bucket.

Primitive types provide these operations automatically.

User-defined types must provide compatible hash and equality implementations before they can be used as keys.

| Key Type           | Example Hash Strategy                                                       |
| ------------------ | ----------------- |
| int              |key % bucketCount                                                         |
| char             | ASCII(key) % bucketCount                                           |
| std::string     | Sum of ASCII values or Polynomial Rolling Hash |
| User-defined types | Custom hash function provided for that type                                 |


For string keys

```cpp
hash = (sum of ASCII values of all characters) % bucketCount;
```

Properties

- Same key always generates the same bucket
- Different keys may generate the same bucket
- Fast computation
- Easy to understand
- Suitable for educational implementation

---

## Load Factor

The HashMap maintains

```
Load Factor

=
Number of Elements
-------------------
Number of Buckets
```

When the load factor exceeds the predefined threshold

```
0.75
```

the HashMap automatically performs **Rehashing**.

---

## Rehash Strategy

During rehashing

1. Allocate a new bucket array.
2. Double the number of buckets.
3. Recompute the hash value of every stored key.
4. Insert every key-value pair into the new bucket array.
5. Free the old bucket array.

Rehashing prevents excessive collisions and maintains efficient average-case performance.

Since the bucket count changes during rehashing, every stored key must be hashed again to determine its new bucket index.

Existing bucket indexes cannot be reused.

---

## Object Ownership

The HashMap object owns

- Every bucket
- Every HashNode
- Every collision chain

Responsibilities include

- Allocating bucket arrays
- Allocating HashNodes
- Linking collision chains
- Destroying every allocated node
- Destroying bucket arrays
- Preventing memory leaks

---

## Destructor Strategy

Destructor algorithm

1. Visit every bucket.
2. Traverse every collision chain.
3. Invoke the destructor of every HashNode.
4. Release the node's raw memory using free().
5. Release the bucket array.
6. Reset internal members.

---

## Copy Strategy

The HashMap **will not share buckets or nodes**.

Instead,

every copied HashMap receives its own

- Bucket array
- Collision chains
- HashNodes

During copying

- Allocate a new bucket array.
- Allocate raw memory for each HashNode.
- Construct new HashNodes using placement new.
- Copy the key and value into the new node.
- Rebuild every collision chain.

This prevents

- Double free
- Dangling pointers
- Shared ownership
- Memory corruption

---

# Section 3 – Complexity Analysis

| Operation | Best | Average | Worst | Reason |
|------------|------|----------|--------|--------|
| set() | O(1) | O(1) | O(n) | Direct bucket access; worst case when all keys collide |
| get() | O(1) | O(1) | O(n) | Direct bucket lookup; worst case traverses an entire chain |
| remove() | O(1) | O(1) | O(n) | Removes from a bucket chain; worst case traverses entire chain |
| contains() | O(1) | O(1) | O(n) | Searches only the corresponding bucket chain |
| size() | O(1) | O(1) | O(1) | Maintained using elementCount |
| loadFactor() | O(1) | O(1) | O(1) | Computed using stored counters |
| isEmpty() | O(1) | O(1) | O(1) | Checks elementCount |
| clear() | O(n) | O(n) | O(n) | Deletes every stored node |
| print() | O(n) | O(n) | O(n) | Visits every bucket and every node |
| rehash() | O(n) | O(n) | O(n) | Reinserts every stored element into the new bucket array |


The average-case complexities assume

- A good hash function.
- Uniform distribution of keys.
- A controlled load factor through automatic rehashing.

Without these assumptions, average O(1) isn't guaranteed.

---

# Section 4 – Design Decisions

## Decision 1

### Separate Chaining instead of Linear Probing

**Chosen because**

- Simpler implementation
- Easy deletion
- Collision handling is straightforward
- Integrates naturally with the Linked List already implemented
- Better educational value for understanding pointer-based structures

---

## Decision 2

### Maintain Element Count

Maintaining an internal element count allows

- O(1) size()
- Fast load factor calculation
- Efficient rehash decisions

---

## Decision 3

### Manual Memory Management

The HashMap separates raw memory allocation from object construction.

Raw memory for the bucket array and every HashNode is allocated using

```cpp
malloc()
```

Objects are then constructed within the allocated memory using C++ placement `new`.

Before releasing memory, the destructor of each object is invoked explicitly, after which the raw memory is released using

```cpp
free()
```

This approach provides explicit control over memory allocation, object lifetime, and deallocation while supporting both primitive and user-defined types. It also aligns with the educational objective of understanding low-level memory management and object ownership.

---

## Decision 4

### Automatic Rehashing

The HashMap will automatically grow whenever the load factor exceeds

```
0.75
```

This helps

- Reduce collisions
- Maintain O(1) average lookup
- Improve overall performance

---

## Decision 5

### Deep Copy

Every HashMap object owns its own

- Bucket array
- HashNodes
- Collision chains

Copying creates

- Independent bucket arrays
- Independent nodes
- Independent ownership

This avoids

- Double free
- Dangling pointers
- Shared ownership

---

## Decision 6

### Generic Design Using Templates

The HashMap will be implemented as a template class rather than restricting it to specific data types.

Chosen because

- Increases reusability
- Supports any key and value types
- Eliminates duplicate implementations
- Keeps the Collections Library consistent with the Dynamic Array and Linked List

---