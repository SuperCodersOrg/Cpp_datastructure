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

// Test 4: Modifying elements through reference returned by get()
TEST(DynamicArrayGetTest, ModifyViaGet) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);

  arr.get(0) = 10;
  arr.get(1) += 20;
  arr.get(2) = arr.get(0) + arr.get(1);

  EXPECT_EQ(arr.get(0), 10);
  EXPECT_EQ(arr.get(1), 22);
  EXPECT_EQ(arr.get(2), 32);
}

// Test 5: Boundary indices for get()
TEST(DynamicArrayGetTest, BoundaryIndices) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);
  arr.append(30);

  // First index
  EXPECT_EQ(arr.get(0), 10);
  // Last index
  EXPECT_EQ(arr.get(arr.size() - 1), 30);
}
