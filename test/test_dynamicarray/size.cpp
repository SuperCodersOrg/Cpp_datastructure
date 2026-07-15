#include "dynamicarray.h"
#include <gtest/gtest.h>

// Test 1: Size of a newly constructed array is 0
TEST(DynamicArraySizeTest, InitialSizeIsZero) {
  DynamicArray<int> arr;
  EXPECT_EQ(arr.size(), 0);
}

// Test 2: Size increases when appending elements
TEST(DynamicArraySizeTest, SizeIncreasesOnAppend) {
  DynamicArray<int> arr;
  
  arr.append(10);
  EXPECT_EQ(arr.size(), 1);

  arr.append(20);
  EXPECT_EQ(arr.size(), 2);

  arr.append(30);
  EXPECT_EQ(arr.size(), 3);
}

// Test 3: Size increases when inserting elements
TEST(DynamicArraySizeTest, SizeIncreasesOnInsert) {
  DynamicArray<int> arr;
  
  arr.insert(0, 10);
  EXPECT_EQ(arr.size(), 1);

  arr.insert(1, 20);
  EXPECT_EQ(arr.size(), 2);

  arr.insert(0, 5);
  EXPECT_EQ(arr.size(), 3);
}

// Test 4: Size decreases when removing elements
TEST(DynamicArraySizeTest, SizeDecreasesOnRemove) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);
  arr.append(30);

  EXPECT_EQ(arr.size(), 3);

  arr.remove(1);
  EXPECT_EQ(arr.size(), 2);

  arr.remove(0);
  EXPECT_EQ(arr.size(), 1);

  arr.remove(0);
  EXPECT_EQ(arr.size(), 0);
}

// Test 5: Size resets to 0 after clear
TEST(DynamicArraySizeTest, SizeResetsOnClear) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);
  
  EXPECT_EQ(arr.size(), 2);
  
  arr.clear();
  EXPECT_EQ(arr.size(), 0);
}
