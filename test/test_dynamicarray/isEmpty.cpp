#include "dynamicarray.h"
#include <gtest/gtest.h>

// Test 1: Newly created array is empty
TEST(DynamicArrayIsEmptyTest, EmptyOnCreation) {
  DynamicArray<int> arr;
  EXPECT_TRUE(arr.isEmpty());
}

// Test 2: Array is not empty after appending elements
TEST(DynamicArrayIsEmptyTest, NotEmptyAfterAppend) {
  DynamicArray<int> arr;
  arr.append(10);
  EXPECT_FALSE(arr.isEmpty());
}

// Test 3: Array is not empty after inserting elements
TEST(DynamicArrayIsEmptyTest, NotEmptyAfterInsert) {
  DynamicArray<int> arr;
  arr.insert(0, 100);
  EXPECT_FALSE(arr.isEmpty());
}

// Test 4: Array returns to empty after clearing all elements
TEST(DynamicArrayIsEmptyTest, EmptyAfterClear) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  
  EXPECT_FALSE(arr.isEmpty());
  
  arr.clear();
  EXPECT_TRUE(arr.isEmpty());
}

// Test 5: Array returns to empty after removing all elements
TEST(DynamicArrayIsEmptyTest, EmptyAfterRemoveAll) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);

  arr.remove(1);
  EXPECT_FALSE(arr.isEmpty());

  arr.remove(0);
  EXPECT_TRUE(arr.isEmpty());
}
