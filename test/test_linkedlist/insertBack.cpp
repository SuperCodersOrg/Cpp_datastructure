#include "linkedlist.h"
#include <gtest/gtest.h>
#include <string>

// Test 1: Insert into empty list
TEST(LinkedListInsertBackTest, InsertIntoEmpty) {
  LinkedList<int> list;
  list.insertBack(42);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 42);
}

// Test 2: Multiple insertions at back
TEST(LinkedListInsertBackTest, InsertMultiple) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);
  EXPECT_EQ(list.get(2), 30);
}

// Test 3: Beginner test case using std::string
TEST(LinkedListInsertBackTest, StringInsertBack) {
  LinkedList<std::string> list;
  list.insertBack("Apple");
  list.insertBack("Banana");

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), "Apple");
  EXPECT_EQ(list.get(1), "Banana");
}

// Test 4: Insert a larger number of elements at back
TEST(LinkedListInsertBackTest, InsertLargeNumberOfElements) {
  LinkedList<int> list;
  const int count = 100;
  for (int i = 0; i < count; ++i) {
    list.insertBack(i);
  }
  EXPECT_EQ(list.size(), count);
  EXPECT_EQ(list.get(0), 0);
  EXPECT_EQ(list.get(count - 1), count - 1);
}

