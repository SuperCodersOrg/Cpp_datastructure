# Journal Entry – Day 02

**Project:** Collections Library (C++)  
**Component:** Linked List  
**Phase:** Design Proposal  
**Date:** 07 July 2026

---

# Introduction

Today, I continued the development of the **Collections Library** by designing the **Linked List** component. Unlike the Dynamic Array, a Linked List stores elements as independently allocated nodes connected through pointers rather than a contiguous block of memory. The primary objective of today's work was to understand pointer-based data structures, design the overall architecture of the Linked List, and establish a complete implementation blueprint before writing any code.

---

# Architecture Selection

The first major task was selecting the most appropriate Linked List architecture.

I evaluated both:

- Singly Linked List
- Doubly Linked List

While comparing these implementations, I considered several factors, including:

- Memory consumption
- Implementation complexity
- Ease of traversal
- Insertion and deletion efficiency
- Suitability for the Collections Library

After careful analysis, I selected the **Singly Linked List** because it satisfies all project requirements while maintaining lower memory overhead and a simpler implementation.

---

# Public API Design

After selecting the architecture, I designed the complete Public API for the Linked List.

I identified all operations that users would require, including:

- Insertion operations
- Deletion operations
- Element access
- Searching
- Utility functions
- Object lifecycle management

While designing the API, I ensured that every function had a clearly defined responsibility and that the interface remained simple, reusable, and consistent with the Dynamic Array component developed previously.

---

# Internal Representation

The next stage involved designing the internal representation of the Linked List.

I created the internal **Node** structure and identified the required data members for both the node and the Linked List itself.

The design included:

- Node structure
- Data field
- Pointer to the next node
- Head pointer
- Element count

I also created multiple memory diagrams illustrating:

- Empty Linked List
- Single-node Linked List
- Multi-node Linked List
- Node traversal
- Node deletion

These diagrams helped visualize how nodes are connected through pointers and how traversal occurs during different operations.

---

# Memory Management Strategy

A significant portion of today's work focused on understanding memory ownership.

Unlike the Dynamic Array, which owns one contiguous block of heap memory, the Linked List owns multiple independently allocated nodes.

I designed an ownership model where:

- The Linked List object owns every dynamically allocated node.
- Every node is allocated independently on the heap.
- The destructor becomes responsible for releasing every allocated node.
- Memory leaks are prevented through proper ownership and destruction.

This design established a clear relationship between the Linked List object and its dynamically allocated nodes.

---

# Complexity Analysis

After completing the structural design, I prepared a detailed complexity analysis for every public operation.

Instead of considering only pointer manipulation, I separated each operation into:

- Traversal cost
- Pointer update cost
- Memory allocation cost

This approach provided a more accurate understanding of why many Linked List operations have linear time complexity even though pointer updates themselves require constant time.

---

# Design Decisions

The final stage of today's work involved documenting every major architectural decision.

These included:

- Choosing a Singly Linked List instead of a Doubly Linked List.
- Using dynamic memory allocation for each node.
- Defining the ownership model.
- Planning destructor responsibilities.
- Preparing for Rule of Three support.
- Maintaining consistency between memory diagrams, complexity analysis, and the Public API.

Documenting these decisions provided clear justification for every aspect of the design.

---

# Output

By the end of the day, I completed the first draft of the Linked List Design Proposal.

Compared to the Dynamic Array, today's work provided a much deeper understanding of pointer-based programming, heap memory management, node ownership, and object lifetime.

Creating memory diagrams before implementation significantly improved my understanding of how nodes are created, linked together, traversed, and eventually destroyed.

The completed design document now serves as a detailed blueprint for the implementation phase and will help minimize implementation errors by resolving architectural decisions in advance.

---

# Key Learnings

- The difference between contiguous memory and pointer-based memory organization.
- The advantages and disadvantages of Singly and Doubly Linked Lists.
- The importance of selecting the simplest architecture that satisfies project requirements.
- How Linked Lists organize data using independently allocated heap nodes.
- The role of the head pointer in managing the entire data structure.
- The importance of object ownership in preventing memory leaks.
- Why traversal dominates the complexity of most Linked List operations.
- The value of memory diagrams in understanding pointer relationships and object lifetime.
- The importance of documenting architectural decisions before implementation.

---
