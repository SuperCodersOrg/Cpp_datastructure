#include "dynamicarray.h"
#include <gtest/gtest.h>

// Test 1: Assign an array to itself
TEST(DynamicArrayAssignmentTest, SelfAssignment) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);

  DynamicArray<int> &self = arr;
  arr = self;

  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr.get(0), 10);
  EXPECT_EQ(arr.get(1), 20);
}

// Test 2: Assign an empty array
TEST(DynamicArrayAssignmentTest, AssignEmptyArray) {
  DynamicArray<int> arr1;
  DynamicArray<int> arr2;

  arr2 = arr1;

  EXPECT_TRUE(arr2.isEmpty());
  EXPECT_EQ(arr2.size(), 0);
}

// Test 3: Assign a smaller array to a larger array
TEST(DynamicArrayAssignmentTest, AssignSmallerArray) {
  DynamicArray<int> arr1;
  arr1.append(1);

  DynamicArray<int> arr2;
  arr2.append(10);
  arr2.append(20);
  arr2.append(30);

  arr2 = arr1;

  EXPECT_EQ(arr2.size(), 1);
  EXPECT_EQ(arr2.get(0), 1);

  // Source should remain unchanged
  EXPECT_EQ(arr1.size(), 1);
  EXPECT_EQ(arr1.get(0), 1);
}

// Test 4: Assign a larger array to a smaller array
TEST(DynamicArrayAssignmentTest, AssignLargerArray) {
  DynamicArray<int> arr1;
  arr1.append(100);
  arr1.append(200);
  arr1.append(300);

  DynamicArray<int> arr2;
  arr2.append(1);

  arr2 = arr1;

  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2.get(0), 100);
  EXPECT_EQ(arr2.get(1), 200);
  EXPECT_EQ(arr2.get(2), 300);
}

// Test 5: Assignment creates a deep copy
TEST(DynamicArrayAssignmentTest, DeepCopy) {
  DynamicArray<int> arr1;
  arr1.append(5);

  DynamicArray<int> arr2;
  arr2 = arr1;

  arr2.get(0) = 10;

  EXPECT_EQ(arr1.get(0), 5);
  EXPECT_EQ(arr2.get(0), 10);
}

// Test 6: Chained assignment (arr3 = arr2 = arr1)
TEST(DynamicArrayAssignmentTest, ChainedAssignment) {
  DynamicArray<int> arr1;
  arr1.append(42);
  arr1.append(84);

  DynamicArray<int> arr2;
  DynamicArray<int> arr3;

  arr3 = arr2 = arr1;

  EXPECT_EQ(arr1.size(), 2);
  EXPECT_EQ(arr2.size(), 2);
  EXPECT_EQ(arr3.size(), 2);

  EXPECT_EQ(arr3.get(0), 42);
  EXPECT_EQ(arr3.get(1), 84);
}

// Helper struct to track destructors during assignment
struct DestructTracker {
  static int destructCount;
  int value;
  DestructTracker(int val) : value(val) {}
  ~DestructTracker() {
    destructCount++;
  }
};
int DestructTracker::destructCount = 0;

// Test 7: Assigning to an array with elements ensures proper destructor calls for overwritten elements
TEST(DynamicArrayAssignmentTest, AssignmentDestruction) {
  DynamicArray<DestructTracker> arr1;
  arr1.append(DestructTracker(100));

  DynamicArray<DestructTracker> arr2;
  arr2.append(DestructTracker(1));
  arr2.append(DestructTracker(2));

  // Reset destruct count before assignment
  DestructTracker::destructCount = 0;

  // arr2 has size 2, arr1 has size 1
  arr2 = arr1;

  // The 2 elements originally in arr2 should be destroyed
  EXPECT_EQ(arr2.size(), 1);
  EXPECT_EQ(arr2.get(0).value, 100);
  EXPECT_EQ(DestructTracker::destructCount, 2);
}
