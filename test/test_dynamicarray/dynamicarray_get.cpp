#include "dynamicarray.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test 1: Get elements at valid indices
TEST(DynamicArrayGetTest, GetValidIndices) {
  DynamicArray<int> arr;
  arr.append(100);
  arr.append(200);

  EXPECT_EQ(arr.get(0), 100);
  EXPECT_EQ(arr.get(1), 200);

  // Modify an element using get()
  arr.get(0) = 150;
  EXPECT_EQ(arr.get(0), 150);
}

// Test 2: Get elements from a const array
TEST(DynamicArrayGetTest, GetFromConstArray) {
  DynamicArray<int> arr;
  arr.append(500);

  const DynamicArray<int> &constArr = arr;

  EXPECT_EQ(constArr.get(0), 500);
}

// Test 3: Get with invalid indices
TEST(DynamicArrayGetTest, GetInvalidIndices) {
  DynamicArray<int> arr;
  arr.append(10);

  EXPECT_THROW(arr.get(-1), std::out_of_range);
  EXPECT_THROW(arr.get(1), std::out_of_range);

  const DynamicArray<int> &constArr = arr;

  EXPECT_THROW(constArr.get(-1), std::out_of_range);
  EXPECT_THROW(constArr.get(1), std::out_of_range);
}