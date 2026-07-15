#ifndef REDISLITE_TPP
#define REDISLITE_TPP

#include "dynamicarray.h"
#include <cctype>
#include <iostream>
#include <redislite.h>
#include <sstream>
#include <string>

// Constructor
inline RedisLite::RedisLite() {}

// Helper to retrieve a value (for testing)
inline bool RedisLite::get(const std::string &key, std::string &value) {
  return store.get(key, value);
}

// Runs the interactive CLI REPL
inline void RedisLite::run() {
  std::string input;
  while (true) {
    std::cout << "RedisLite> ";
    if (!std::getline(std::cin, input)) {
      break;
    }
    if (!processCommand(input)) {
      break;
    }
  }
}

// Helper to tokenize input string, handling double/single quotes and spaces
inline DynamicArray<std::string> RedisLite::tokenize(const std::string &input) const {
  DynamicArray<std::string> tokens;
  std::string token;
  bool inDoubleQuotes = false;
  bool inSingleQuotes = false;

  for (size_t i = 0; i < input.length(); ++i) {
    char c = input[i];
    if (inDoubleQuotes) {
      if (c == '\\' && i + 1 < input.length() && (input[i + 1] == '"' || input[i + 1] == '\\')) {
        token.push_back(input[i + 1]);
        i++;
      } else if (c == '"') {
        inDoubleQuotes = false;
        tokens.append(token);
        token.clear();
      } else {
        token.push_back(c);
      }
    } else if (inSingleQuotes) {
      if (c == '\\' && i + 1 < input.length() && (input[i + 1] == '\'' || input[i + 1] == '\\')) {
        token.push_back(input[i + 1]);
        i++;
      } else if (c == '\'') {
        inSingleQuotes = false;
        tokens.append(token);
        token.clear();
      } else {
        token.push_back(c);
      }
    } else {
      if (c == '"') {
        if (!token.empty()) {
          tokens.append(token);
          token.clear();
        }
        inDoubleQuotes = true;
      } else if (c == '\'') {
        if (!token.empty()) {
          tokens.append(token);
          token.clear();
        }
        inSingleQuotes = true;
      } else if (std::isspace(static_cast<unsigned char>(c))) {
        if (!token.empty()) {
          tokens.append(token);
          token.clear();
        }
      } else {
        token.push_back(c);
      }
    }
  }

  if (!token.empty()) {
    tokens.append(token);
  }

  return tokens;
}

// Helper to convert string to uppercase
inline std::string RedisLite::toUpper(std::string str) const {
  for (char &c : str) {
    c = std::toupper(static_cast<unsigned char>(c));
  }
  return str;
}

// Parses input tokens and validates command syntax
inline bool RedisLite::parseInput(const DynamicArray<std::string> &tokens) {
  if (tokens.isEmpty()) {
    return true;
  }

  std::string command = toUpper(tokens.get(0));

  if (command == "SET") {
    if (tokens.size() != 3) {
      std::cout << "Error: SET requires a key and a value\n";
      return false;
    }
  } else if (command == "GET") {
    if (tokens.size() != 2) {
      std::cout << "Error: GET requires a key\n";
      return false;
    }
  } else if (command == "DEL") {
    if (tokens.size() != 2) {
      std::cout << "Error: DEL requires a key\n";
      return false;
    }
  } else if (command == "EXISTS") {
    if (tokens.size() != 2) {
      std::cout << "Error: EXISTS requires a key\n";
      return false;
    }
  } else if (command == "COUNT") {
    if (tokens.size() != 1) {
      std::cout << "Error: COUNT does not take any arguments\n";
      return false;
    }
  } else if (command == "CLEAR") {
    if (tokens.size() != 1) {
      std::cout << "Error: CLEAR does not take any arguments\n";
      return false;
    }
  } else if (command == "HELP") {
    if (tokens.size() != 1) {
      std::cout << "Error: HELP does not take any arguments\n";
      return false;
    }
  } else if (command == "EXIT") {
    if (tokens.size() != 1) {
      std::cout << "Error: EXIT does not take any arguments\n";
      return false;
    }
  } else {
    std::cout << "Error: Unknown command '" << tokens.get(0) << "'\n";
    return false;
  }

  return true;
}

// Processes input, validates it and dispatches to appropriate handler
inline bool RedisLite::processCommand(const std::string &input) {
  DynamicArray<std::string> tokens = tokenize(input);

  if (tokens.isEmpty()) {
    return true;
  }

  if (!parseInput(tokens)) {
    return true; // continue prompt
  }

  std::string command = toUpper(tokens.get(0));

  if (command == "EXIT") {
    std::cout << "Exiting Redis Lite...\n";
    return false;
  } else if (command == "HELP") {
    printHelp();
  } else if (command == "SET") {
    handleSet(tokens.get(1), tokens.get(2));
  } else if (command == "GET") {
    handleGet(tokens.get(1));
  } else if (command == "DEL") {
    handleDel(tokens.get(1));
  } else if (command == "EXISTS") {
    handleExists(tokens.get(1));
  } else if (command == "COUNT") {
    handleCount();
  } else if (command == "CLEAR") {
    handleClear();
  }

  return true;
}

// Command Handlers
inline void RedisLite::handleSet(const std::string &key, const std::string &value) {
  store.insert(key, value);
  std::cout << "OK\n";
}

inline void RedisLite::handleGet(const std::string &key) {
  std::string value;
  if (store.get(key, value)) {
    std::cout << value << "\n";
  } else {
    std::cout << "Error: Key not found\n";
  }
}

inline void RedisLite::handleDel(const std::string &key) {
  if (store.exists(key)) {
    store.remove(key);
    std::cout << "OK\n";
  } else {
    std::cout << "Error: Key not found\n";
  }
}

inline void RedisLite::handleExists(const std::string &key) {
  if (store.exists(key)) {
    std::cout << "true\n";
  } else {
    std::cout << "false\n";
  }
}

inline void RedisLite::handleCount() { std::cout << store.size() << "\n"; }

inline void RedisLite::handleClear() {
  store.clear();
  std::cout << "OK\n";
}

inline void RedisLite::printHelp() const {
  std::cout << "Supported commands:\n"
            << "  SET <key> <value> - Store or update a key-value pair\n"
            << "  GET <key>         - Retrieve the value of a key\n"
            << "  DEL <key>         - Delete a key-value pair\n"
            << "  EXISTS <key>      - Check if a key exists\n"
            << "  COUNT             - Show number of key-value pairs\n"
            << "  CLEAR             - Clear all key-value pairs\n"
            << "  HELP              - Show this help message\n"
            << "  EXIT              - Exit Redis Lite\n";
}

#endif
