#include "linkedlist.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test 1: Delete front on a list with single element
TEST(LinkedListDeleteFrontTest, DeleteFrontSingle) {
  LinkedList<int> list;
  list.insertBack(42);

  list.deleteFront();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}

// Test 2: Delete front on a list with multiple elements
TEST(LinkedListDeleteFrontTest, DeleteFrontMultiple) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  list.deleteFront();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 20);

  list.deleteFront();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 30);
}

// Test 3: Delete front on an empty list throws
TEST(LinkedListDeleteFrontTest, DeleteFrontEmpty) {
  LinkedList<int> list;
  EXPECT_THROW(list.deleteFront(), std::out_of_range);
}

// Test 4: Delete front repeatedly until list is empty
TEST(LinkedListDeleteFrontTest, DeleteFrontUntilEmpty) {
  LinkedList<int> list;
  list.insertBack(1);
  list.insertBack(2);
  list.insertBack(3);
  
  list.deleteFront();
  list.deleteFront();
  list.deleteFront();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}
