#include "linkedlist.h"
#include <gtest/gtest.h>

// Test 1: Self assignment
TEST(LinkedListAssignmentTest, SelfAssignment) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);

  LinkedList<int> &self = list;
  list = self;

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);
}

// Test 2: Assign empty list
TEST(LinkedListAssignmentTest, AssignEmptyList) {
  LinkedList<int> list1;
  LinkedList<int> list2;
  list2.insertBack(100);

  list2 = list1;
  EXPECT_TRUE(list2.isEmpty());
  EXPECT_EQ(list2.size(), 0);
}

// Test 3: Assign smaller to larger list
TEST(LinkedListAssignmentTest, AssignSmallerList) {
  LinkedList<int> list1;
  list1.insertBack(5);

  LinkedList<int> list2;
  list2.insertBack(10);
  list2.insertBack(20);

  list2 = list1;
  EXPECT_EQ(list2.size(), 1);
  EXPECT_EQ(list2.get(0), 5);
}

// Test 4: Assign larger to smaller list
TEST(LinkedListAssignmentTest, AssignLargerList) {
  LinkedList<int> list1;
  list1.insertBack(10);
  list1.insertBack(20);
  list1.insertBack(30);

  LinkedList<int> list2;
  list2.insertBack(5);

  list2 = list1;
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list2.get(0), 10);
  EXPECT_EQ(list2.get(1), 20);
  EXPECT_EQ(list2.get(2), 30);
}

// Test 5: Deep copy on assignment
TEST(LinkedListAssignmentTest, DeepCopy) {
  LinkedList<int> list1;
  list1.insertBack(5);

  LinkedList<int> list2;
  list2 = list1;
  list2.get(0) = 10;

  EXPECT_EQ(list1.get(0), 5);
  EXPECT_EQ(list2.get(0), 10);
}

// Test 6: Chained assignment
TEST(LinkedListAssignmentTest, ChainedAssignment) {
  LinkedList<int> list1;
  list1.insertBack(10);
  list1.insertBack(20);

  LinkedList<int> list2, list3;
  list3 = list2 = list1;

  EXPECT_EQ(list3.size(), 2);
  EXPECT_EQ(list3.get(0), 10);
  EXPECT_EQ(list3.get(1), 20);
}

// Helper struct to track destructors during assignment
namespace {
struct DestructTracker {
  static int destructCount;
  int value;
  DestructTracker(int val) : value(val) {}
  ~DestructTracker() { destructCount++; }
};
int DestructTracker::destructCount = 0;
}


// Test 7: Old elements destroyed on assignment
TEST(LinkedListAssignmentTest, DestructionOnAssignment) {
  LinkedList<DestructTracker> list1;
  list1.insertBack(DestructTracker(100));

  LinkedList<DestructTracker> list2;
  list2.insertBack(DestructTracker(1));
  list2.insertBack(DestructTracker(2));

  DestructTracker::destructCount = 0;
  list2 = list1;

  // The 2 elements originally in list2 should be destroyed
  EXPECT_EQ(list2.size(), 1);
  EXPECT_EQ(DestructTracker::destructCount, 2);
}

// Test 8: Self assignment on an empty list
TEST(LinkedListAssignmentTest, AssignToSelfEmpty) {
  LinkedList<int> list;
  LinkedList<int> &self = list;
  list = self;
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}
