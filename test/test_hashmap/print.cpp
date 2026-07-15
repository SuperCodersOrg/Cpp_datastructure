#include "hashmap.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

// Test print() on empty map
TEST(HashMapPrintTest, PrintEmpty) {
  HashMap<int, std::string> myMap;

  // Redirect std::cout
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  myMap.print();

  // Restore std::cout
  std::cout.rdbuf(oldCout);

  EXPECT_EQ(buffer.str(), "");
}

// Test print() on non-empty map
TEST(HashMapPrintTest, PrintNonEmpty) {
  HashMap<int, std::string> myMap;
  myMap.insert(1, "one");

  // Redirect std::cout
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  myMap.print();

  // Restore std::cout
  std::cout.rdbuf(oldCout);

  EXPECT_EQ(buffer.str(), "1 : one\n");
}

// Test debugPrint() on empty map
TEST(HashMapPrintTest, DebugPrintEmpty) {
  HashMap<int, std::string> myMap(4);

  // Redirect std::cout
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  myMap.debugPrint();

  // Restore std::cout
  std::cout.rdbuf(oldCout);

  std::string expected = 
    "Bucket 0 : 0\n"
    "Bucket 1 : 0\n"
    "Bucket 2 : 0\n"
    "Bucket 3 : 0\n";
  EXPECT_EQ(buffer.str(), expected);
}

// Custom hash that forces collisions
namespace {
struct BeginnerConstantHash {
  size_t operator()(const int &) const {
    return 2;
  }
};
}

// Test debugPrint() on map with collisions
TEST(HashMapPrintTest, DebugPrintWithCollisions) {
  HashMap<int, std::string, BeginnerConstantHash> myMap(4);
  myMap.insert(1, "one");
  myMap.insert(2, "two");

  // Redirect std::cout
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  myMap.debugPrint();

  // Restore std::cout
  std::cout.rdbuf(oldCout);

  std::string expected = 
    "Bucket 0 : 0\n"
    "Bucket 1 : 0\n"
    "Bucket 2 : 2\n"
    "Bucket 3 : 0\n";
  EXPECT_EQ(buffer.str(), expected);
}

// Test print() output with multiple elements
TEST(HashMapPrintTest, PrintMultipleElements) {
  HashMap<int, std::string, BeginnerConstantHash> myMap(4);
  myMap.insert(1, "one");
  myMap.insert(2, "two");

  // Redirect std::cout
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  myMap.print();

  // Restore std::cout
  std::cout.rdbuf(oldCout);

  // Both should print, because they are inserted in front, 2 should print first
  std::string expected = "2 : two\n1 : one\n";
  EXPECT_EQ(buffer.str(), expected);
}

// Test print() output after clearing the map
TEST(HashMapPrintTest, PrintAfterClear) {
  HashMap<int, std::string> myMap;
  myMap.insert(1, "one");
  myMap.clear();

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
  myMap.print();
  std::cout.rdbuf(oldCout);

  EXPECT_EQ(buffer.str(), "");
}
