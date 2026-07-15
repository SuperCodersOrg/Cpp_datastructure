# Day 08 Build Log

**Project:** Collections Library (C++)  
**Component:** Redis Lite & Test Suite Expansion  
**Phase:** Core REPL Implementation & Modular Test Migration  
**Date:** 15 July 2026

---

# Shift 01 (10:00 AM – 01:30 PM)

## Goal

Split the big test file into smaller test files for `DynamicArray`, `LinkedList`, and `HashMap`. Put these tests in clean folders, compile them using GoogleTest, and write more tests for `HashMap` to make sure everything works correctly.

## Work Completed

- **DynamicArray Test Refactoring**:
  - Split the old tests into 11 separate files under `test/test_dynamicarray/`: `constructor.cpp`, `assignment.cpp`, `append.cpp`, `remove.cpp`, `insert.cpp`, `get.cpp`, `size.cpp`, `capacity.cpp`, `isEmpty.cpp`, `clear.cpp`, and `destructor.cpp`.
  - Removed old or double tests.
- **LinkedList Test Expansion**:
  - Created 15 smaller test files under `test/test_linkedlist/` to test `LinkedList` constructors, copy rules, inserting, deleting, search, and clear functions.
- **HashMap Test Suites**:
  - Added 7 test files under `test/test_hashmap/` to test `HashMap` behaviors:
    - `constructor.cpp`: Tests default size and setup.
    - `assignment.cpp`: Tests copying maps and making sure they use separate memory.
    - `insert.cpp`: Tests how the map handles collisions and resizing (rehashing).
    - `get.cpp`: Tests finding items in the map.
    - `remove.cpp`: Tests deleting items from the map.
    - `clear.cpp`: Tests emptying the map safely.
    - `print.cpp`: Tests printing the map contents.
- **CMake Configuration Update**:
  - Updated [CMakeLists.txt](file:///Users/tanishdogra/Cpp_datastructure/CMakeLists.txt) to include all the new test files.

## Outcome

All new test files compile and run successfully.

---

# Shift 02 (02:30 PM – 06:00 PM)

## Goal

Build the interactive command-line app "Redis Lite". It will use our custom `HashMap` to store data. The app needs to support spaces inside keys and values by handling quotes. Expose standard database commands and write unit tests for the command-line app.

## Work Completed

- **Implemented RedisLite Core**:
  - Created [redislite.h](file:///Users/tanishdogra/Cpp_datastructure/include/redislite.h) and [redislite.tpp](file:///Users/tanishdogra/Cpp_datastructure/src/redislite.tpp) using our own `HashMap<std::string, std::string>` and `DynamicArray<std::string>`.
  - Wrote a tokenizer (`tokenize()`) to split user input by spaces. It supports single quotes (`'`) and double quotes (`"`) so users can type inputs with spaces (like `SET "my key" "my value"`). It also supports escaped quotes (`\"` and `\'`).
  - Wrote `parseInput` to check if commands have the right number of inputs (for example, checking that `SET` has two parameters).
  - Wrote the main loop in `RedisLite::run()` to read and run user commands.
  - Added a `--redis` flag in [main.cpp](file:///Users/tanishdogra/Cpp_datastructure/main.cpp) to start the app.
- **Exposed Database Commands**:
  - `SET <key> <value>`: Saves or updates a key and value (prints `OK`).
  - `GET <key>`: Gets the value of a key (or prints `Error: Key not found`).
  - `DEL <key>`: Deletes a key (prints `OK` or `Error: Key not found`).
  - `EXISTS <key>`: Prints `true` or `false` to show if a key is there.
  - `COUNT`: Prints the number of items in the database.
  - `CLEAR`: Deletes everything in the database (prints `OK`).
  - `HELP`: Lists all commands.
  - `EXIT`: Closes the application.
- **Implemented Redis Lite Unit Tests**:
  - Added 7 test suites under `test/test_redislite/` to test command-line features:
    - `tokenize.cpp`: Tests separating text (quotes, spaces, escapes).
    - `set.cpp`: Tests setting values and checking for syntax errors.
    - `get.cpp`: Tests getting values.
    - `del.cpp`: Tests deleting values.
    - `exists.cpp`: Tests checking if keys exist.
    - `clear.cpp`: Tests clearing the database.
    - `count.cpp`: Tests counting database items.

## Outcome

All 220 tests (for DynamicArray, LinkedList, HashMap, and RedisLite) pass successfully with zero errors. The Redis Lite app works perfectly using `./simple --redis`.
