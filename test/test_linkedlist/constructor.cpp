#include "linkedlist.h"
#include <gtest/gtest.h>
#include <string>

// Test 1: Default constructor
TEST(LinkedListConstructorTest, DefaultConstructor) {
  LinkedList<int> list;
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}

// Test 2: Copy constructor on empty list
TEST(LinkedListConstructorTest, CopyEmptyList) {
  LinkedList<int> list1;
  LinkedList<int> list2(list1);
  EXPECT_TRUE(list2.isEmpty());
  EXPECT_EQ(list2.size(), 0);
}

// Test 3: Copy constructor on non-empty list
TEST(LinkedListConstructorTest, CopyNonEmptyList) {
  LinkedList<int> list1;
  list1.insertBack(10);
  list1.insertBack(20);
  list1.insertBack(30);

  LinkedList<int> list2(list1);
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list2.get(0), 10);
  EXPECT_EQ(list2.get(1), 20);
  EXPECT_EQ(list2.get(2), 30);
}

// Test 4: Deep copy verification
TEST(LinkedListConstructorTest, DeepCopy) {
  LinkedList<int> list1;
  list1.insertBack(100);

  LinkedList<int> list2(list1);
  list2.get(0) = 200;

  EXPECT_EQ(list1.get(0), 100);
  EXPECT_EQ(list2.get(0), 200);
}

// Helper struct to track copy constructions
namespace {
struct CopyTracker {
  static int copyCount;
  int value;
  CopyTracker(int val) : value(val) {}
  CopyTracker(const CopyTracker& other) : value(other.value) {
    copyCount++;
  }
  ~CopyTracker() = default;
};
int CopyTracker::copyCount = 0;
}


// Test 5: Element copy tracking
TEST(LinkedListConstructorTest, ElementCopyTracking) {
  CopyTracker::copyCount = 0;
  LinkedList<CopyTracker> list1;
  list1.insertBack(CopyTracker(5));
  list1.insertBack(CopyTracker(10));

  CopyTracker::copyCount = 0;
  LinkedList<CopyTracker> list2(list1);

  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(CopyTracker::copyCount, 2);
  EXPECT_EQ(list2.get(0).value, 5);
  EXPECT_EQ(list2.get(1).value, 10);
}

// Test 6: Copy constructor on single element list
TEST(LinkedListConstructorTest, CopySingleElementList) {
  LinkedList<int> list1;
  list1.insertBack(42);
  LinkedList<int> list2(list1);
  EXPECT_EQ(list2.size(), 1);
  EXPECT_EQ(list2.get(0), 42);
}
