#include "linkedlist.h"
#include <gtest/gtest.h>

// Test 1: Initial state
TEST(LinkedListIsEmptyTest, InitialEmpty) {
  LinkedList<int> list;
  EXPECT_TRUE(list.isEmpty());
}

// Test 2: Not empty after insert
TEST(LinkedListIsEmptyTest, NotEmpty) {
  LinkedList<int> list;
  list.insertFront(10);
  EXPECT_FALSE(list.isEmpty());
}

// Test 3: Empty after deletes/clear
TEST(LinkedListIsEmptyTest, EmptyAfterDeletesClear) {
  LinkedList<int> list;
  list.insertFront(10);
  list.insertBack(20);

  list.deleteFront();
  EXPECT_FALSE(list.isEmpty());

  list.deleteBack();
  EXPECT_TRUE(list.isEmpty());

  list.insertFront(30);
  EXPECT_FALSE(list.isEmpty());

  list.clear();
  EXPECT_TRUE(list.isEmpty());
}

// Test 4: Verify isEmpty transitions multiple times
TEST(LinkedListIsEmptyTest, EmptyStateTransitions) {
  LinkedList<int> list;
  EXPECT_TRUE(list.isEmpty());
  list.insertBack(100);
  EXPECT_FALSE(list.isEmpty());
  list.deleteFront();
  EXPECT_TRUE(list.isEmpty());
}
