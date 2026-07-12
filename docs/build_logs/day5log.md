# Day 05 Build Log

**Project:** Collections Library (C++)  
**Component:** HashMap  
**Phase:** Implementation Phase  
**Date:** 11 July 2026

---

# Shift 01 (09:45 AM – 01:15 PM)

## Goal

Implement the `HashMap` class skeleton, custom hashing functors, specialized templates for primitive keys, memory-management helper functions, and the Rule of Three.

## Work Completed

- Created [hashmap.h](file:///Users/tanishdogra/Cpp_datastructure/include/hashmap.h) for declarations and [hashmap.tpp](file:///Users/tanishdogra/Cpp_datastructure/src/hashmap.tpp) for template implementations.
- Defined the nested `HashNode` structure and generic `HashMap` skeleton.
- Created `DefaultHash` template functor and implemented specializations for primitive/arithmetic data types:
  - Standard arithmetic/integer types (direct casting).
  - `float` (hashing binary bits via `std::memcpy`).
  - `double` (hashing binary bits via `std::memcpy` and XOR folding).
  - `long double` (using FNV-1a hash algorithm over the bytes).
  - Pointers `T*` (casting to `size_t`).
  - `std::nullptr_t` (returns 0).
- Implemented helper methods for manual memory management:
  - `allocateBuckets(capacity)` using `std::malloc`.
  - `destroyBuckets()` for deep memory cleanup of the bucket array.
  - `createNode(k, v)` using placement `new` to construct nodes in raw memory.
  - `destroyNode(node)` invoking `~HashNode` explicitly and calling `std::free`.
  - `clear()` to free all chain nodes while retaining the bucket array size.
- Implemented class Constructors and Destructor:
  - `HashMap(int initialCapacity)` allocating raw memory.
  - Destructor calling `destroyBuckets()`.
- Implemented the Rule of Three to support safe resource copying:
  - Copy Constructor implementing deep copy, protected by try-catch blocks to prevent leaks on exception.
  - Copy Assignment Operator using temporary bucket allocations and exception safety guards.

## Outcome

Successfully completed the layout of the Hash Map, specialized hashing logic, custom memory hooks, and a resource-safe Rule of Three implementation.

---

# Shift 02 (02:30 PM – 06:00 PM)

## Goal

Develop the core public interface functions for the `HashMap`, implement separate chaining collision traversal, enable dynamic resizing through rehashing, and write unit/driver verification tests.

## Work Completed

- Implemented core public CRUD operations:
  - `insert(key, value)` with dynamic load factor monitoring.
  - `get(key, value)` with traversal along collision chains.
  - `remove(key)` to delete specific nodes and adjust pointers.
  - `contains(key)` for key lookup queries.
- Implemented helper operations:
  - `size()` returning the number of elements.
  - `isEmpty()` checking if elements exist.
  - `loadFactor()` calculating the current fill ratio.
  - `clear()` resetting map elements.
- Implemented `rehash(newCapacity)` helper which dynamically doubles capacity when the load factor exceeds `0.75` and redistributes chain nodes without re-allocation.
- Implemented print formatting helper:
  - Created `details::is_streamable` SFINAE trait.
  - Developed `print()` displaying all buckets and chains, printing `<unstreamable>` for keys or values not supporting `std::ostream` output.
- Integrated testing logic in [main.cpp](file:///Users/tanishdogra/Cpp_datastructure/main.cpp) validating:
  - Copy constructors and copy assignments.
  - Key types like pointers, custom types, float/double, `nullptr_t`, and integers.
  - Dynamic resizing (threshold checks) and chain printing.

## Outcome

The HashMap template is fully operational, successfully passes compilation and test coverage, handles rehashing seamlessly, and handles custom types with strong exception safety.
