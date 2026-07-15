#include "linkedlist.h"
#include <gtest/gtest.h>
#include <string>

// Test 1: Search in empty list
TEST(LinkedListSearchTest, SearchEmpty) {
  LinkedList<int> list;
  EXPECT_FALSE(list.search(42));
}

// Test 2: Search for present value
TEST(LinkedListSearchTest, SearchPresent) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  EXPECT_TRUE(list.search(10));
  EXPECT_TRUE(list.search(20));
  EXPECT_TRUE(list.search(30));
}

// Test 3: Search for missing value
TEST(LinkedListSearchTest, SearchMissing) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);

  EXPECT_FALSE(list.search(15));
  EXPECT_FALSE(list.search(40));
}

// Test 4: Beginner test case for searching string values
TEST(LinkedListSearchTest, SearchStringValues) {
  LinkedList<std::string> list;
  list.insertBack("Apple");
  list.insertBack("Banana");

  EXPECT_TRUE(list.search("Apple"));
  EXPECT_TRUE(list.search("Banana"));
  EXPECT_FALSE(list.search("Cherry"));
}

// Test 5: Search for elements when duplicate values exist
TEST(LinkedListSearchTest, SearchDuplicateValues) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(10);
  EXPECT_TRUE(list.search(10));
  EXPECT_TRUE(list.search(20));
  EXPECT_FALSE(list.search(30));
}

