# Day 03 Build Log

**Project:** Collections Library (C++)  
**Component:** HashMap  
**Phase:** Design Proposal  
**Date:** 08 July 2026

---

# Shift 01 (09:30 AM – 11:30 AM)

## Goal

Begin the design proposal for the HashMap by understanding the requirements of an associative container, identifying the required operations, and selecting an appropriate collision handling strategy before implementation.

## Work Completed

- Reviewed the functional requirements of the HashMap component.
- Studied how associative containers differ from linear data structures.
- Identified all required public operations for the HashMap.
- Designed the initial public API.
- Compared different collision resolution techniques.
- Evaluated Separate Chaining, Linear Probing, Quadratic Probing, and Double Hashing.

## Problem Encountered

Selecting the most suitable collision handling strategy while keeping the implementation educational, reusable, and compatible with the existing Collections Library.

## What I Tried

Compared each collision handling technique based on:

- Memory consumption
- Ease of implementation
- Collision handling efficiency
- Deletion complexity
- Dynamic resizing support
- Integration with the previously implemented Linked List

## Outcome

Selected **Separate Chaining** as the collision resolution strategy because it provides simple insertion and deletion while naturally reusing the Linked List implementation already developed in the Collections Library.

## Learning

The collision handling strategy influences the overall architecture of a HashMap. Choosing the simplest design that satisfies the project requirements improves maintainability while reducing implementation complexity.

---

# Shift 02 (11:45 AM – 01:45 PM)

## Goal

Design the internal memory representation of the HashMap and define the ownership model before implementation.

## Work Completed

- Designed the internal `HashNode` structure.
- Planned the bucket array representation.
- Designed the relationship between buckets and collision chains.
- Created memory diagrams showing bucket arrays connected to linked collision chains.
- Defined ownership responsibilities for buckets and nodes.
- Planned the destructor strategy.
- Designed the Rule of Three requirements.

## Problem Encountered

Determining how dynamically allocated objects should be managed while supporting both primitive data types and user-defined template types.

## What I Tried

Studied the difference between:

- Memory allocation
- Object construction
- Object destruction
- Memory deallocation

Compared:

- `new` / `delete`
- `malloc()` / `free()`
- Placement `new`

Created multiple memory diagrams illustrating:

- Raw memory allocation
- Object construction
- Heap ownership
- Destructor execution
- Memory release

## Outcome

Finalized a manual memory management strategy where:

- Raw memory is allocated using `malloc()`.
- Objects are constructed using placement `new`.
- Destructors are invoked explicitly.
- Raw memory is released using `free()`.

## Learning

Memory allocation and object construction are independent operations. Separating them provides complete control over object lifetime while allowing the HashMap to support generic template types safely.

---

# Shift 03 (02:30 PM – 04:45 PM)

## Goal

Design the hashing workflow, collision handling process, automatic resizing mechanism, and analyze the complexity of every operation.

## Work Completed

- Designed the complete hashing workflow.
- Planned bucket index calculation.
- Defined key requirements for generic template types.
- Designed collision chain traversal.
- Planned duplicate key handling.
- Designed load factor calculation.
- Planned automatic rehashing.
- Prepared complexity analysis for every public operation.
- Documented the reasoning behind each complexity estimate.

## Problem Encountered

Understanding how generic template keys should be converted into bucket indexes while maintaining flexibility for future user-defined data types.

## What I Tried

Analyzed hashing strategies for:

- Integer keys
- Character keys
- String keys
- User-defined types

Studied the relationship between:

- Hash values
- Bucket indexes
- Equality comparison
- Collision chains
- Rehashing

## Outcome

Completed the design for:

- Hash function workflow
- Bucket index computation
- Key requirements
- Collision handling
- Load factor calculation
- Automatic rehashing
- Complexity analysis

## Learning

Hashing determines the candidate bucket, while equality comparison identifies the correct key within the collision chain. Efficient HashMaps require both operations working together.

---

# Shift 04 (05:30 PM – 07:15 PM)

## Goal

Review the complete HashMap design proposal, validate consistency across every section, and prepare the implementation blueprint.

## Work Completed

- Reviewed the complete public API.
- Verified the internal memory representation.
- Updated the memory management policy.
- Reviewed object ownership responsibilities.
- Updated the copy strategy.
- Updated the destructor strategy.
- Validated the complexity analysis.
- Reviewed all design decisions for consistency.
- Cross-checked memory diagrams against the planned implementation.

## Problem Encountered

Maintaining consistency across the entire design proposal after introducing placement `new`, explicit destructor calls, and support for generic template types.

## What I Tried

Performed a complete design review by validating:

- Public API
- Memory management policy
- Internal memory representation
- HashNode design
- Bucket organization
- Hash function workflow
- Rehash strategy
- Complexity analysis
- Ownership model
- Design decisions

## Outcome

Completed the first draft of the HashMap Design Proposal, establishing a comprehensive architectural blueprint for the implementation phase.

## Learning

A well-designed HashMap depends not only on efficient hashing algorithms but also on correct memory management, object ownership, collision handling, and consistent architectural decisions. Investing time in design significantly reduces implementation uncertainty.

---

# End of Day Summary

## Objectives Achieved

- ✔ Reviewed HashMap project requirements
- ✔ Designed the complete public API
- ✔ Selected **Separate Chaining** as the collision resolution strategy
- ✔ Designed the internal `HashNode` structure
- ✔ Planned the bucket array representation
- ✔ Designed heap memory organization
- ✔ Defined object ownership responsibilities
- ✔ Finalized the manual memory management strategy using `malloc()`, placement `new`, explicit destructor calls, and `free()`
- ✔ Designed the hashing workflow
- ✔ Planned automatic rehashing
- ✔ Defined generic key requirements
- ✔ Completed the complexity analysis
- ✔ Planned deep copy behavior
- ✔ Considered Rule of Three requirements
- ✔ Completed the first draft of the HashMap Design Proposal

---

# Key Technical Takeaways

- A HashMap stores key-value pairs by mapping keys into buckets using deterministic hash functions.
- Separate Chaining resolves collisions through linked lists stored inside bucket arrays.
- Memory allocation and object construction are separate operations. Raw memory is allocated using `malloc()`, objects are constructed using placement `new`, destructors are invoked explicitly, and memory is finally released using `free()`.
- The HashMap owns every bucket, every collision chain, and every dynamically allocated node.
- Hashing determines the candidate bucket, while equality comparison identifies the correct key inside a collision chain.
- Automatic rehashing maintains efficient average-case performance by controlling the load factor.
- Completing API design, memory management, ownership rules, complexity analysis, and architectural decisions before implementation provides a solid engineering foundation for building reliable generic containers.