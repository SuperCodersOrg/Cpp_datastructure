# Day 07 Build Log

**Project:** Collections Library (C++)  
**Component:** Testing Integration & Redis Lite Design  
**Phase:** CTest Migration & Design Proposal  
**Date:** 14 July 2026

---

# Shift 01 (10:00 AM – 01:30 PM)

## Goal

Integrate the GoogleTest framework with CMake's CTest harness, migrate and run all test targets through `ctest`, expand coverage by implementing unit tests for the `LinkedList` component, and resolve any functional and structural bugs found during execution.

## Work Completed

- Configured `CMakeLists.txt` with `enable_testing()` and linked the `runTests` target with GoogleTest library templates (`GTest::gtest` and `GTest::gtest_main`).
- Appended all 15 new `test/test_linkedlist/` unit test source files to the `runTests` executable target in [CMakeLists.txt](file:///Users/tanishdogra/Cpp_datastructure/CMakeLists.txt).
- Addressed CTest registration issues by running a clean configure steps to wipe CMakeCache.txt and discover all tests correctly.
- Resolved functional errors flagged during `LinkedList` test execution:
  - **Self-Assignment Fault**: Added reference check `if (this == &other)` to [linkedlist.tpp](file:///Users/tanishdogra/Cpp_datastructure/src/linkedlist.tpp) assignment operator to prevent lists from clearing themselves.
  - **Null Dereferences in Deletions**: Handled empty lists in `deleteFront()`, `deleteBack()`, and `deleteAt()`, ensuring they throw `std::out_of_range` exceptions.
  - **Single Element Deletion**: Fixed `deleteBack()` logic when `head->next == nullptr` to correctly release the head node and set `head = nullptr`.

## Outcome

Successfully configured the test harness. Run execution on CMake CTest passed with 100% success rate (117/117 unit tests passed) with zero memory leaks.

---

# Shift 02 (02:30 PM – 06:00 PM)

## Goal

Design the Redis Lite application architecture, draft the interface specifications, and write the initial Design Proposal documentation.

## Work Completed

- Created [Redislite_design.md](file:///Users/tanishdogra/Cpp_datastructure/docs/design/Redislite_design.md) in the `docs/design` folder to log the architectural choices of the new database system.
- Designed the high-level layered structure: Command Line (CLI) <-> Redis Lite Application Layer <-> Generic HashMap Storage Engine <-> Buckets & Chain memory.
- Defined the class interface for `RedisLite` to contain private command handlers (`handleSet`, `handleGet`, `handleDelete`, `handleExists`, `handleCount`, `handleClear`) and parsed helper helper methods (`parseInput`, `processCommand`).
- Started drafting API specifications including return types, parameters, exception guarantees, time complexities, and design rationales for the core execution loop.

## Outcome

The design document for Redis Lite has been initiated and structured. The basic architecture and class API have been drafted, but the proposal is still a work-in-progress and remains incomplete.

