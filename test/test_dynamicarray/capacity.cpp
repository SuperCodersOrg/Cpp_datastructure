#include "dynamicarray.h"
#include <gtest/gtest.h>

// Test 1: Initial capacity is 1
TEST(DynamicArrayCapacityTest, InitialCapacityIsOne) {
  DynamicArray<int> arr;
  EXPECT_EQ(arr.capacity(), 1);
}

// Test 2: Capacity increases (doubles) correctly on resize trigger
TEST(DynamicArrayCapacityTest, CapacityGrowthOnResize) {
  DynamicArray<int> arr;
  
  // Capacity: 1, Size: 0
  arr.append(1);
  EXPECT_EQ(arr.capacity(), 1);
  EXPECT_EQ(arr.size(), 1);

  // Appending second element triggers resize (1 * 2 = 2)
  arr.append(2);
  EXPECT_EQ(arr.capacity(), 2);
  EXPECT_EQ(arr.size(), 2);

  // Appending third element triggers resize (2 * 2 = 4)
  arr.append(3);
  EXPECT_EQ(arr.capacity(), 4);
  EXPECT_EQ(arr.size(), 3);
}

// Test 3: Capacity does not shrink when elements are removed
TEST(DynamicArrayCapacityTest, CapacityDoesNotShrinkOnRemove) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3); // Capacity is now 4

  int currentCapacity = arr.capacity();
  EXPECT_EQ(currentCapacity, 4);

  arr.remove(2);
  EXPECT_EQ(arr.capacity(), currentCapacity);

  arr.remove(1);
  EXPECT_EQ(arr.capacity(), currentCapacity);

  arr.remove(0);
  EXPECT_EQ(arr.capacity(), currentCapacity);
}

// Test 4: Capacity does not shrink when array is cleared
TEST(DynamicArrayCapacityTest, CapacityDoesNotShrinkOnClear) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3); // Capacity is now 4

  int currentCapacity = arr.capacity();
  EXPECT_EQ(currentCapacity, 4);

  arr.clear();
  EXPECT_EQ(arr.capacity(), currentCapacity);
}
