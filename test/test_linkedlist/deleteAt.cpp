#include "linkedlist.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test 1: Delete at index 0
TEST(LinkedListDeleteAtTest, DeleteAtZero) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);

  list.deleteAt(0);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 20);
}

// Test 2: Delete in middle
TEST(LinkedListDeleteAtTest, DeleteInMiddle) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  list.deleteAt(1); // delete element 20

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 30);
}

// Test 3: Delete at last index
TEST(LinkedListDeleteAtTest, DeleteAtLast) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  list.deleteAt(2); // deletes 30

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);
}

// Test 4: Delete at invalid indices throws out_of_range
TEST(LinkedListDeleteAtTest, DeleteAtInvalidIndices) {
  LinkedList<int> list;
  EXPECT_THROW(list.deleteAt(-1), std::out_of_range);
  EXPECT_THROW(list.deleteAt(0), std::out_of_range);

  list.insertBack(10);
  EXPECT_THROW(list.deleteAt(1), std::out_of_range);
}

// Test 5: Delete at index 0 on a single element list
TEST(LinkedListDeleteAtTest, DeleteAtSingleElement) {
  LinkedList<int> list;
  list.insertBack(42);
  list.deleteAt(0);
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}
