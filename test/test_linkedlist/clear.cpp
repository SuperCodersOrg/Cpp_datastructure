#include "linkedlist.h"
#include <gtest/gtest.h>

// Test 1: Clear empty list
TEST(LinkedListClearTest, ClearEmpty) {
  LinkedList<int> list;
  list.clear();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}

// Test 2: Clear non-empty list
TEST(LinkedListClearTest, ClearNonEmpty) {
  LinkedList<int> list;
  list.insertBack(1);
  list.insertBack(2);

  list.clear();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}

// Test 3: Clear idempotent
TEST(LinkedListClearTest, ClearIdempotent) {
  LinkedList<int> list;
  list.insertBack(100);

  list.clear();
  EXPECT_NO_THROW(list.clear());
  EXPECT_NO_THROW(list.clear());
  EXPECT_TRUE(list.isEmpty());
}

// Test 4: Reuse after clear
TEST(LinkedListClearTest, AppendAfterClear) {
  LinkedList<int> list;
  list.insertBack(1);
  list.clear();

  list.insertBack(10);
  list.insertFront(5);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 5);
  EXPECT_EQ(list.get(1), 10);
}

// Test 5: Clear a large list
TEST(LinkedListClearTest, ClearLargeList) {
  LinkedList<int> list;
  for (int i = 0; i < 100; ++i) {
    list.insertBack(i);
  }
  list.clear();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}
