#include "linkedlist.h"
#include <gtest/gtest.h>
#include <string>

// Test 1: Insert into empty list
TEST(LinkedListInsertFrontTest, InsertIntoEmpty) {
  LinkedList<int> list;
  list.insertFront(42);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 42);
}

// Test 2: Multiple insertions at front
TEST(LinkedListInsertFrontTest, InsertMultiple) {
  LinkedList<int> list;
  list.insertFront(10);
  list.insertFront(20);
  list.insertFront(30);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), 30);
  EXPECT_EQ(list.get(1), 20);
  EXPECT_EQ(list.get(2), 10);
}

// Test 3: Beginner test case using std::string
TEST(LinkedListInsertFrontTest, StringInsertFront) {
  LinkedList<std::string> list;
  list.insertFront("Banana");
  list.insertFront("Apple");

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), "Apple");
  EXPECT_EQ(list.get(1), "Banana");
}

// Test 4: Insert a larger number of elements at front
TEST(LinkedListInsertFrontTest, InsertLargeNumberOfElements) {
  LinkedList<int> list;
  const int count = 100;
  for (int i = 0; i < count; ++i) {
    list.insertFront(i);
  }
  EXPECT_EQ(list.size(), count);
  EXPECT_EQ(list.get(0), count - 1);
  EXPECT_EQ(list.get(count - 1), 0);
}

