# Journal Entry – Day 01

**Project:** Collections Library (C++)  
**Component:** Dynamic Array  
**Phase:** Design Proposal  
**Date:** 06 July 2026

---

# Introduction

Today marked the beginning of the **Collections Library** project with the design of the **Dynamic Array** component. Instead of immediately starting implementation, the focus was placed on understanding the problem domain and preparing a comprehensive software design that would serve as the foundation for the implementation phase.

---

# Public API Design

The first task was to define the overall objective of the Dynamic Array and identify the functionality that the data structure should provide.

While designing the Public API, I initially found it challenging to distinguish between operations that should be exposed to users and those that should remain internal implementation details.

To resolve this, I analyzed the responsibilities of a Dynamic Array and categorized its operations into:

- Object lifecycle management
- Element insertion and deletion
- Data access
- Utility and state inspection

This analysis helped me design a clean, reusable, and well-structured Public API.

---

# Internal Representation

After completing the Public API, I designed the internal representation of the Dynamic Array.

I identified the private data members required to manage dynamically allocated memory and finalized the use of:

- A pointer to heap memory
- Current size
- Current capacity

Planning these data members helped me understand how the Dynamic Array would organize memory internally and interact with the heap during runtime.

---

# Memory Management Strategy

During the second session, I focused on designing the memory management strategy and defining the ownership model of the container.

One of the most important design decisions involved selecting the resizing strategy.

I compared multiple approaches, including:

- Fixed-size increment
- Percentage-based growth
- Capacity doubling

After evaluating their performance characteristics, I selected the **capacity doubling strategy** because it minimizes reallocations while providing efficient amortized insertion performance.

---

# Rule of Three

To ensure proper ownership of dynamically allocated memory, I documented the **Rule of Three**.

This included planning the behavior of:

- Copy Constructor
- Copy Assignment Operator
- Destructor

Understanding these concepts helped reinforce how dynamically allocated resources should be managed safely throughout an object's lifetime.

---

# Complexity Analysis

I completed the complexity analysis for every public operation of the Dynamic Array.

For each function, I documented:

- Best-case complexity
- Average-case complexity
- Worst-case complexity
- The reasoning behind each complexity estimate

This exercise improved my understanding of how different operations affect the overall performance of the data structure.

---

# Design Decisions

Finally, I documented every major design decision made during the day.

For each decision, I recorded:

- The selected approach
- Alternative approaches considered
- The justification for the final selection

This process helped ensure that every architectural decision was supported by clear technical reasoning.

---

# Output

By the end of the day, I completed the first draft of the Dynamic Array Design Proposal.

Preparing the complete architecture before implementation significantly improved my understanding of:

- Memory management
- Object ownership
- Public API design
- Internal representation
- Software architecture
- Engineering documentation

The completed design document now serves as a clear blueprint for the implementation phase and is expected to reduce implementation uncertainty while improving overall code quality.

---

# Key Learnings

- The importance of designing software before implementation.
- The difference between the Public API and the Internal Representation.
- How Dynamic Arrays organize memory using contiguous heap allocation.
- The role of size and capacity in dynamic storage management.
- Why capacity doubling provides efficient amortized insertion.
- The importance of the Rule of Three when managing dynamic memory.
- How complexity analysis guides implementation decisions.
- The value of documenting design decisions before writing code.

---

