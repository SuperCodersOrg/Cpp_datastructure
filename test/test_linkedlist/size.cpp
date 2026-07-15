#include "linkedlist.h"
#include <gtest/gtest.h>

// Test 1: Initial size is 0
TEST(LinkedListSizeTest, InitialSize) {
  LinkedList<int> list;
  EXPECT_EQ(list.size(), 0);
}

// Test 2: Size increases/decreases correctly
TEST(LinkedListSizeTest, SizeChanges) {
  LinkedList<int> list;
  
  list.insertFront(10);
  EXPECT_EQ(list.size(), 1);

  list.insertBack(20);
  EXPECT_EQ(list.size(), 2);

  list.insertAt(1, 15);
  EXPECT_EQ(list.size(), 3);

  list.deleteFront();
  EXPECT_EQ(list.size(), 2);

  list.deleteBack();
  EXPECT_EQ(list.size(), 1);

  list.deleteAt(0);
  EXPECT_EQ(list.size(), 0);
}

// Test 3: Size after clear
TEST(LinkedListSizeTest, SizeClear) {
  LinkedList<int> list;
  list.insertBack(1);
  list.insertBack(2);
  
  EXPECT_EQ(list.size(), 2);
  list.clear();
  EXPECT_EQ(list.size(), 0);
}

// Test 4: Size of a large list
TEST(LinkedListSizeTest, SizeOfLargeList) {
  LinkedList<int> list;
  for (int i = 0; i < 50; ++i) {
    list.insertBack(i);
  }
  EXPECT_EQ(list.size(), 50);
}
