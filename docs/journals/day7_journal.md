# Journal Entry – Day 07

**Project:** Collections Library (C++)  
**Component:** Testing Integration & Redis Lite Design  
**Phase:** CTest Migration & Design Proposal  
**Date:** 14 July 2026

---

# Introduction

Today, I focused on migrating our testing infrastructure to CMake's native `CTest` framework alongside GoogleTest (`gtest`), writing a comprehensive test suite for the `LinkedList` component, resolving several edge-case errors flagged during this test integration, and starting the formal documentation for the **Redis Lite Design Proposal**. Redis Lite will serve as an interactive application layer utilizing our custom `HashMap` as its core storage engine.

---

# CTest Integration & Unit Testing (Morning Session)

During the morning session, we set up `CTest` to run all unit tests automatically and added the full suite of unit tests for the `LinkedList` component. We encountered and resolved several errors:

- **CTest / CMake Test Discovery Errors**:
  - *Issue*: After adding the new `test/test_linkedlist/*.cpp` source files to `CMakeLists.txt`, `ctest` failed to execute the new test cases, reporting only the old `DynamicArray` tests.
  - *Cause*: CMake cached the previous targets, and `gtest_discover_tests` did not trigger a rebuild of the test registry correctly.
  - *Resolution*: Cleared the `build/` directory CMake cache, ran `cmake ..` to rebuild, and successfully registered all 117 tests (combining both `DynamicArray` and `LinkedList`).
- **LinkedList Self-Assignment Bug**:
  - *Issue*: Testing list assignment (`LinkedListAssignmentTest`) revealed that assigning a list to itself (e.g., `list = list;`) completely wiped its contents instead of doing nothing.
  - *Cause*: The implementation of `operator=` in `linkedlist.tpp` called `clear()` immediately before copying the nodes, resulting in losing the pointers to the original list nodes.
  - *Resolution*: Implemented a reference check guard (`if (this == &other) return *this;`) at the beginning of the assignment operator.
- **Empty List Deletion Boundary Errors**:
  - *Issue*: Testing `deleteBack()` and `deleteFront()` on empty or single-element lists triggered segmentation faults.
  - *Cause*: Standard deletion functions did not gracefully handle cases where `head` was `nullptr` or `head->next` was `nullptr`, resulting in invalid dereferences.
  - *Resolution*: Implemented checks to throw `std::out_of_range` on empty lists, and correctly updated the `head` pointer to `nullptr` when the last element in the list was removed.

---

# Redis Lite Design Proposal (Evening Session)

In the evening session, we initiated the design phase for **Redis Lite**:

- **Database CLI Architecture**:
  - Outlined the architecture of the command-line interface (CLI) to process commands interactively via a Read-Evaluate-Print Loop (REPL).
  - Drafted the public API for the `RedisLite` class containing methods to run the loop (`run()`), split inputs (`parseInput()`), and delegate commands (`processCommand()`).
- **Integrating HashMap as Storage Engine**:
  - Configured `RedisLite` to use our custom `HashMap<std::string, std::string>` to map database keys to their values.
  - Planned individual handler functions to execute commands like `SET`, `GET`, `DEL`, `EXISTS`, `COUNT`, and `CLEAR` directly on the underlying hashmap.
- **Design Proposal Document**:
  - Formally began writing [Redislite_design.md](file:///Users/tanishdogra/Cpp_datastructure/docs/design/Redislite_design.md), outlining the project scope, high-level layering, and public API documentation. The design is currently incomplete and remains a work-in-progress.

---

# Key Learnings

- **Automated Test Automation (CTest)**: Using CTest simplifies running multi-suite unit tests in parallel and gathering quick code coverage statistics.
- **Edge-Case Validation**: Testing edge-cases (self-assignment, empty container state, single-element collections) is critical to developing robust data structures before integrating them into application layers.
- **Modularity & Separation of Concerns**: Keeping the CLI layer (`RedisLite`) completely decoupled from the data structures (`HashMap`) ensures both are clean, extensible, and easier to test independently.
