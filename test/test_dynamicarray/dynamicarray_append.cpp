#include "dynamicarray.h"
#include <gtest/gtest.h>
#include <string>

// Test 1: Append a single element to an empty array
TEST(DynamicArrayAppendTest, AppendToEmptyArray) {
  DynamicArray<int> arr;

  arr.append(42);

  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get(0), 42);
  EXPECT_FALSE(arr.isEmpty());
}

// Test 2: Append multiple elements and verify they are stored in order
TEST(DynamicArrayAppendTest, AppendMultipleElements) {
  DynamicArray<std::string> arr;

  arr.append("hello");
  arr.append("world");
  arr.append("test");

  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(0), "hello");
  EXPECT_EQ(arr.get(1), "world");
  EXPECT_EQ(arr.get(2), "test");
}

// Test 3: Append enough elements to trigger automatic resizing
TEST(DynamicArrayAppendTest, AppendResizesArray) {
  DynamicArray<int> arr;

  EXPECT_EQ(arr.capacity(), 1);

  for (int i = 1; i <= 10; i++) {
    arr.append(i);
  }

  EXPECT_EQ(arr.size(), 10);
  EXPECT_GE(arr.capacity(), 10);

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(arr.get(i), i + 1);
  }
}