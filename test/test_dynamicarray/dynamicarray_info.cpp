#include "dynamicarray.h"
#include <gtest/gtest.h>

// Test 1: Information for an empty array
TEST(DynamicArrayInfoTest, EmptyArray) {
  DynamicArray<int> arr;

  EXPECT_TRUE(arr.isEmpty());
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(arr.capacity(), 1);
}

// Test 2: Size and capacity after appending and removing elements
TEST(DynamicArrayInfoTest, SizeAndCapacityChanges) {
  DynamicArray<int> arr;

  arr.append(10);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_FALSE(arr.isEmpty());

  arr.append(20);
  arr.append(30);

  EXPECT_EQ(arr.size(), 3);
  EXPECT_GE(arr.capacity(), 3);

  arr.remove(1);

  EXPECT_EQ(arr.size(), 2);
  EXPECT_FALSE(arr.isEmpty());
  EXPECT_GE(arr.capacity(), 2);
}