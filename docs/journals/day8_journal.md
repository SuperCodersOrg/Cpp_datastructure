# Journal Entry – Day 08

**Project:** Collections Library (C++)  
**Component:** Redis Lite & Test Suite Expansion  
**Phase:** Core REPL Implementation & Modular Test Migration  
**Date:** 15 July 2026

---

# Introduction

Today was a great day. We stopped working on low-level data structures and built our first application: **Redis Lite**. 
To prepare for this, we cleaned up our tests in the morning. We split the big tests for `DynamicArray`, `LinkedList`, and `HashMap` into separate files. In the afternoon, we built and tested `RedisLite`, which is a simple interactive database that uses our custom `HashMap` to store information.

---

# Splitting the Tests (Morning Session)

As our project grows, having all tests in one huge file makes it hard to find errors. I cleaned this up today:
- **Split Tests into Files**: We put DynamicArray and LinkedList tests into smaller, single-topic files (like `constructor.cpp`, `assignment.cpp`, and `append.cpp`). This makes it easier to run specific tests.
- **Added HashMap Tests**: We added 7 new test files under `test/test_hashmap/` to make sure our database storage engine works perfectly before building Redis Lite on top of it. We tested copying, inserting, collisions, resizing, and clearing the map.

---

# Building Redis Lite (Evening Session)

In the afternoon, we built **Redis Lite**, a simple terminal database app:
- **Splitting Inputs with Quotes**:
  - Splitting user text by spaces is tricky because keys or values can have spaces in them (for example: `SET "user age" "twenty five"`).
  - I wrote a custom parser in `RedisLite::tokenize` that reads text character-by-character. It handles single quotes (`'`) and double quotes (`"`) correctly, keeps spaces inside quotes, and supports escaped quotes (like `\"`).
- **Verifying Commands**:
  - We wrote code to check if a command has the right inputs before running it. This prevents errors or crashes.
  - We connected terminal commands (`SET`, `GET`, `DEL`, `EXISTS`, `COUNT`, `CLEAR`, `HELP`, `EXIT`) directly to our `HashMap`.
- **Command Line Flag**:
  - You can now start the database by running `./simple --redis` in the terminal.
- **Tests**:
  - We added unit tests for every database command.
  - We now have **220 tests** in total, and all of them pass successfully.

---

# Key Learnings

- **Using Our Own Code**: Building the database shell (`RedisLite`) separately from the storage code (`HashMap`) worked very well. It proves that our custom structures are easy to use in real apps.
- **Handling User Input**: Building a CLI means we must handle unexpected inputs carefully. Dealing with spaces, quotes, and escapes is important so the app does not crash.
- **Small Test Files**: Having separate test files for each feature makes debugging much faster and keeps compiling fast.
