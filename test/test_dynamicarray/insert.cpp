#include "dynamicarray.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Test 1: Insert at the front
TEST(DynamicArrayInsertTest, InsertAtFront) {
  DynamicArray<int> arr;
  arr.append(10);
  arr.append(20);

  arr.insert(0, 5);

  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(0), 5);
  EXPECT_EQ(arr.get(1), 10);
  EXPECT_EQ(arr.get(2), 20);
}

// Test 2: Insert in the middle
TEST(DynamicArrayInsertTest, InsertInMiddle) {
  DynamicArray<std::string> arr;
  arr.append("first");
  arr.append("last");

  arr.insert(1, "middle");

  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(0), "first");
  EXPECT_EQ(arr.get(1), "middle");
  EXPECT_EQ(arr.get(2), "last");
}

// Test 3: Insert at the end
TEST(DynamicArrayInsertTest, InsertAtEnd) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);

  arr.insert(2, 3);

  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(0), 1);
  EXPECT_EQ(arr.get(1), 2);
  EXPECT_EQ(arr.get(2), 3);
}

// Test 4: Insert into an empty array
TEST(DynamicArrayInsertTest, InsertIntoEmptyArray) {
  DynamicArray<int> arr;

  arr.insert(0, 99);

  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr.get(0), 99);
}

// Test 5: Insert causes the array to resize
TEST(DynamicArrayInsertTest, InsertResizesArray) {
  DynamicArray<int> arr;

  arr.append(10);
  arr.insert(0, 5);

  EXPECT_EQ(arr.size(), 2);
  EXPECT_GE(arr.capacity(), 2);
  EXPECT_EQ(arr.get(0), 5);
  EXPECT_EQ(arr.get(1), 10);
}

// Test 6: Insert with an invalid index
TEST(DynamicArrayInsertTest, InsertInvalidIndex) {
  DynamicArray<int> arr;
  arr.append(100);

  EXPECT_THROW(arr.insert(-1, 50), std::out_of_range);
  EXPECT_THROW(arr.insert(2, 50), std::out_of_range);

  DynamicArray<int> emptyArr;
  EXPECT_THROW(emptyArr.insert(1, 50), std::out_of_range);
}

// Test 7: Insert at end behaves like append
TEST(DynamicArrayInsertTest, InsertAtEndBehavesLikeAppend) {
  DynamicArray<int> arr;
  arr.append(1);
  arr.append(2);

  // insert at index equal to size (2)
  arr.insert(2, 3);
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(2), 3);
}

// Test 8: Repeated insert at front
TEST(DynamicArrayInsertTest, RepeatedInsertAtFront) {
  DynamicArray<int> arr;
  arr.insert(0, 30);
  arr.insert(0, 20);
  arr.insert(0, 10);

  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.get(0), 10);
  EXPECT_EQ(arr.get(1), 20);
  EXPECT_EQ(arr.get(2), 30);
}
