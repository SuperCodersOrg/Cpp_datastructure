# Journal Entry – Day 03

**Project:** Collections Library (C++)  
**Component:** HashMap  
**Phase:** Design Proposal  
**Date:** 08 July 2026

---

# Introduction

Today, I continued the development of the **Collections Library** by designing the **HashMap** component. Unlike linear data structures such as Dynamic Arrays and Linked Lists, a HashMap stores data as key-value pairs and uses hashing to provide efficient average-case insertion, searching, and deletion.

The primary objective of today's work was to understand the internal architecture of a HashMap, design its memory organization, define its ownership model, and prepare a complete implementation blueprint before writing any code.

---

# Collision Handling Strategy

The first major architectural decision involved selecting an appropriate collision handling strategy.

I studied and compared multiple approaches, including:

- Separate Chaining
- Linear Probing
- Quadratic Probing
- Double Hashing

While evaluating these techniques, I considered several factors:

- Implementation complexity
- Memory usage
- Ease of insertion
- Ease of deletion
- Dynamic resizing
- Educational value
- Integration with the previously implemented Linked List

After careful analysis, I selected **Separate Chaining** because it provides a simpler implementation, efficient deletion, and naturally reuses the Linked List already developed within the Collections Library.

---

# Public API Design

After selecting the collision handling strategy, I designed the complete Public API for the HashMap.

The interface includes operations for:

- Object construction
- Object destruction
- Insertion and updating
- Searching
- Retrieval
- Deletion
- State inspection
- Utility functions

While designing the API, I ensured that it remained consistent with the interfaces of the Dynamic Array and Linked List, making the Collections Library more uniform and reusable.

---

# Internal Representation

The next stage involved designing the internal representation of the HashMap.

I designed the internal **HashNode** structure responsible for storing:

- Key
- Value
- Pointer to the next node in the collision chain

I also designed the internal bucket array containing pointers to collision chains.

To better understand the data structure, I prepared memory diagrams illustrating:

- Empty bucket arrays
- Collision chains
- Bucket organization
- Heap memory layout
- Object ownership

These diagrams helped visualize how keys are distributed across buckets and how collisions are resolved through linked lists.

---

# Memory Management Strategy

One of the most important concepts explored today was manual memory management for generic containers.

Initially, I planned to allocate memory using only `malloc()` and release it using `free()`. However, after studying template-based containers, I learned that user-defined objects require constructors and destructors to execute correctly.

To support both primitive and user-defined data types, I finalized a memory management strategy that separates memory allocation from object construction.

The final design performs:

- Raw memory allocation using `malloc()`
- Object construction using placement `new`
- Explicit destructor invocation
- Memory deallocation using `free()`

Understanding this separation significantly improved my knowledge of object lifetime and generic programming.

---

# Hashing and Collision Resolution

Another major focus of today's work was understanding how hashing works internally.

I studied how:

- Keys are converted into hash values.
- Hash values are transformed into bucket indexes.
- Different keys can generate identical bucket indexes.
- Collisions are resolved using linked lists.
- Equality comparison is used to locate the correct key inside a collision chain.

I also documented the requirements that every key type must satisfy before it can be stored inside the HashMap.

---

# Load Factor and Rehashing

I designed the load factor calculation used to measure how full the HashMap becomes during insertion.

I learned how excessive collisions reduce performance and how automatic rehashing restores efficiency by:

- Allocating a larger bucket array.
- Recomputing bucket indexes.
- Reinserting every existing key-value pair.
- Releasing the previous bucket array.

This helped me understand why average-case constant-time performance depends on maintaining an appropriate load factor.

---

# Complexity Analysis

After completing the architectural design, I prepared the complexity analysis for every public operation.

For each operation, I documented:

- Best-case complexity
- Average-case complexity
- Worst-case complexity
- The reasoning behind each complexity estimate

I also learned that average-case complexity depends on:

- A good hash function
- Uniform key distribution
- Proper load factor management

---

# Design Decisions

The final stage of today's work involved documenting every major architectural decision.

These included:

- Selecting Separate Chaining
- Designing the HashNode structure
- Choosing manual memory management
- Separating memory allocation from object construction
- Supporting generic templates
- Planning automatic rehashing
- Designing deep copy behavior
- Planning Rule of Three support
- Defining ownership responsibilities

Documenting these decisions provided clear technical justification for every aspect of the HashMap design.

---

# Output

By the end of the day, I completed the first draft of the HashMap Design Proposal.

Today's work significantly expanded my understanding of hashing, collision resolution, manual memory management, placement `new`, object lifetime, and generic programming.

One of the biggest lessons was realizing that allocating memory and constructing objects are two independent operations. Understanding this concept completely changed how I think about dynamic memory management in C++.

Preparing the complete architecture before implementation has provided a clear roadmap for the coding phase and has greatly reduced uncertainty about the overall implementation.

---

# Key Learnings

- The architecture of a HashMap differs fundamentally from linear data structures.
- Separate Chaining provides a simple and effective collision resolution strategy.
- Bucket arrays organize data by storing pointers to collision chains.
- Hashing and equality comparison work together to locate stored elements.
- Memory allocation and object construction are independent operations.
- Placement `new` enables generic containers to support user-defined types safely.
- Proper object ownership prevents memory leaks and ensures safe resource management.
- Automatic rehashing maintains efficient average-case performance.
- Generic template containers require careful planning of memory management and object lifetime.
- Designing before implementation improves code quality and reduces implementation errors.

---

