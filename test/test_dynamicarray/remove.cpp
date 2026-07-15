#include "dynamicarray.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Test 1: Remove the last element
TEST(DynamicArrayRemoveTest, RemoveFromEnd) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);
  arr.append(30);

  arr.remove(2);

  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr.get(0), 10);
  EXPECT_EQ(arr.get(1), 20);
}

// Test 2: Remove the first element
TEST(DynamicArrayRemoveTest, RemoveFromBeginning) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);
  arr.append(30);

  arr.remove(0);

  EXPECT_EQ(arr.size(), 2);
  EXPECT_EQ(arr.get(0), 20);
  EXPECT_EQ(arr.get(1), 30);
}

// Test 3: Remove an element from the middle
TEST(DynamicArrayRemoveTest, RemoveFromMiddle) {
  DynamicArray<std::string> arr;
  arr.append("A");
  arr.append("B");
  arr.append("C");
  arr.append("D");

  arr.remove(1);

  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(0), "A");
  EXPECT_EQ(arr.get(1), "C");
  EXPECT_EQ(arr.get(2), "D");
}

// Test 4: Remove the only element
TEST(DynamicArrayRemoveTest, RemoveOnlyElement) {
  DynamicArray<int> arr;
  arr.append(42);

  arr.remove(0);

  EXPECT_TRUE(arr.isEmpty());
  EXPECT_EQ(arr.size(), 0);
}

// Test 5: Remove with an invalid index
TEST(DynamicArrayRemoveTest, RemoveInvalidIndex) {
  DynamicArray<int> arr;
  arr.append(100);

  EXPECT_THROW(arr.remove(-1), std::out_of_range);
  EXPECT_THROW(arr.remove(1), std::out_of_range);

  DynamicArray<int> emptyArr;
  EXPECT_THROW(emptyArr.remove(0), std::out_of_range);
}

// Test 6: Remove repeatedly until empty
TEST(DynamicArrayRemoveTest, RemoveRepeatedlyUntilEmpty) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);

  arr.remove(1); // removes 2, remaining: 1, 3
  arr.remove(1); // removes 3, remaining: 1
  arr.remove(0); // removes 1, remaining: empty

  EXPECT_EQ(arr.size(), 0);
  EXPECT_TRUE(arr.isEmpty());
}

// Test 7: Append after removing all elements
TEST(DynamicArrayRemoveTest, AppendAfterRemoveAll) {
  DynamicArray<int> arr;
  arr.append(5);
  arr.append(6);

  arr.remove(0);
  arr.remove(0);

  EXPECT_TRUE(arr.isEmpty());

  arr.append(10);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get(0), 10);
}
