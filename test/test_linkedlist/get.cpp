#include "linkedlist.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test 1: Get valid indices
TEST(LinkedListGetTest, GetValid) {
  LinkedList<int> list;
  list.insertBack(100);
  list.insertBack(200);

  EXPECT_EQ(list.get(0), 100);
  EXPECT_EQ(list.get(1), 200);
}

// Test 2: Get from const list
TEST(LinkedListGetTest, GetConst) {
  LinkedList<int> list;
  list.insertBack(500);

  const LinkedList<int> &constList = list;
  EXPECT_EQ(constList.get(0), 500);
}

// Test 3: Modify via reference
TEST(LinkedListGetTest, ModifyViaGet) {
  LinkedList<int> list;
  list.insertBack(10);

  list.get(0) = 20;
  EXPECT_EQ(list.get(0), 20);
}

// Test 4: Get invalid indices throws
TEST(LinkedListGetTest, GetInvalid) {
  LinkedList<int> list;
  EXPECT_THROW(list.get(-1), std::out_of_range);
  EXPECT_THROW(list.get(0), std::out_of_range);

  list.insertBack(10);
  EXPECT_THROW(list.get(1), std::out_of_range);
  
  const LinkedList<int> &constList = list;
  EXPECT_THROW(constList.get(-1), std::out_of_range);
  EXPECT_THROW(constList.get(1), std::out_of_range);
}

// Test 5: Beginner test case for standard index-based loop iteration
TEST(LinkedListGetTest, BasicLoopIteration) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  int expectedValue = 10;
  for (int i = 0; i < list.size(); ++i) {
    EXPECT_EQ(list.get(i), expectedValue);
    expectedValue += 10;
  }
}

// Test 6: Get index zero on a single element list
TEST(LinkedListGetTest, GetSingleElementRange) {
  LinkedList<int> list;
  list.insertBack(42);
  EXPECT_EQ(list.get(0), 42);
  EXPECT_THROW(list.get(1), std::out_of_range);
}

