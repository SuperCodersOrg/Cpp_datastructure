#include "dynamicarray.h"
#include <gtest/gtest.h>

// Test 1: Clear an empty array
TEST(DynamicArrayClearTest, ClearEmptyArray) {
  DynamicArray<int> arr;

  arr.clear();

  EXPECT_TRUE(arr.isEmpty());
  EXPECT_EQ(arr.size(), 0);
}

// Test 2: Clear a non-empty array
TEST(DynamicArrayClearTest, ClearNonEmptyArray) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);

  int oldCapacity = arr.capacity();

  arr.clear();

  EXPECT_TRUE(arr.isEmpty());
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(arr.capacity(), oldCapacity);
}

// Test 3: Append after clearing the array
TEST(DynamicArrayClearTest, AppendAfterClear) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);

  arr.clear();
  arr.append(30);

  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get(0), 30);
}