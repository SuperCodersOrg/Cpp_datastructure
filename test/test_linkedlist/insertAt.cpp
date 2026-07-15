#include "linkedlist.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test 1: Insert at index 0
TEST(LinkedListInsertAtTest, InsertAtZero) {
  LinkedList<int> list;
  list.insertAt(0, 10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 10);

  list.insertAt(0, 5);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 5);
  EXPECT_EQ(list.get(1), 10);
}

// Test 2: Insert in middle
TEST(LinkedListInsertAtTest, InsertInMiddle) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(30);

  list.insertAt(1, 20); // insert at index 1

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);
  EXPECT_EQ(list.get(2), 30);
}

// Test 3: Insert at the end
TEST(LinkedListInsertAtTest, InsertAtEnd) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);

  list.insertAt(2, 30); // insert at index 2

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(2), 30);
}

// Test 4: Insert at invalid indices throws out_of_range
TEST(LinkedListInsertAtTest, InsertInvalidIndices) {
  LinkedList<int> list;
  EXPECT_THROW(list.insertAt(-1, 5), std::out_of_range);
  EXPECT_THROW(list.insertAt(1, 5), std::out_of_range);

  list.insertBack(10);
  EXPECT_THROW(list.insertAt(2, 5), std::out_of_range);
}

// Test 5: Insert at index 1 on a single element list
TEST(LinkedListInsertAtTest, InsertAtEndSingleElement) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertAt(1, 20);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);
}
