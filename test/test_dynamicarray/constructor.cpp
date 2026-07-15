#include "dynamicarray.h"
#include <gtest/gtest.h>
#include <string>

// Test 1: Default constructor
TEST(DynamicArrayConstructorTest, DefaultConstructor) {
    DynamicArray<int> arr;

    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 1);
    EXPECT_TRUE(arr.isEmpty());
}

// Test 2: Default constructor with another type
TEST(DynamicArrayConstructorTest, StringConstructor) {
    DynamicArray<std::string> arr;

    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.isEmpty());
}

// Test 3: Copy constructor for empty array
TEST(DynamicArrayConstructorTest, CopyEmptyArray) {
    DynamicArray<int> arr1;

    DynamicArray<int> arr2(arr1);

    EXPECT_EQ(arr2.size(), 0);
    EXPECT_TRUE(arr2.isEmpty());
}

// Test 4: Copy constructor for non-empty array
TEST(DynamicArrayConstructorTest, CopyNonEmptyArray) {
    DynamicArray<int> arr1;

    arr1.append(10);
    arr1.append(20);
    arr1.append(30);

    DynamicArray<int> arr2(arr1);

    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2.get(0), 10);
    EXPECT_EQ(arr2.get(1), 20);
    EXPECT_EQ(arr2.get(2), 30);
}

// Test 5: Deep copy
TEST(DynamicArrayConstructorTest, DeepCopy) {
    DynamicArray<int> arr1;

    arr1.append(100);

    DynamicArray<int> arr2(arr1);

    arr2.get(0) = 200;

    EXPECT_EQ(arr1.get(0), 100);
    EXPECT_EQ(arr2.get(0), 200);
}

// Test 6: Copy after resize
TEST(DynamicArrayConstructorTest, CopyAfterResize) {
    DynamicArray<int> arr1;

    for (int i = 1; i <= 10; i++) {
        arr1.append(i);
    }

    DynamicArray<int> arr2(arr1);

    EXPECT_EQ(arr2.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr2.get(i), i + 1);
    }
}

// Test 7: Copy of a single element 
TEST(DynamicArrayConstructorTest, CopySingleElement) {
    DynamicArray<int> arr1;

    arr1.append(99);

    DynamicArray<int> arr2(arr1);

    EXPECT_EQ(arr2.size(), 1);
    EXPECT_EQ(arr2.get(0), 99);
}

// Test 8: Copy constructor with complex operations (append, insert, remove)
TEST(DynamicArrayConstructorTest, CopyAfterStructuralOps) {
    DynamicArray<int> arr1;
    arr1.append(1);
    arr1.append(2);
    arr1.insert(1, 10); // 1, 10, 2
    arr1.remove(0);     // 10, 2
    arr1.append(3);     // 10, 2, 3

    DynamicArray<int> arr2(arr1);

    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2.get(0), 10);
    EXPECT_EQ(arr2.get(1), 2);
    EXPECT_EQ(arr2.get(2), 3);
}

// Helper struct to track copy constructions
struct CopyTracker {
    static int copyCount;
    int value;
    CopyTracker(int val) : value(val) {}
    CopyTracker(const CopyTracker& other) : value(other.value) {
        copyCount++;
    }
    ~CopyTracker() = default;
};
int CopyTracker::copyCount = 0;

// Test 9: Copy constructor element tracking (ensures copy constructor of element type is called)
TEST(DynamicArrayConstructorTest, ElementCopyTracking) {
    CopyTracker::copyCount = 0;
    DynamicArray<CopyTracker> arr1;
    arr1.append(CopyTracker(5));
    arr1.append(CopyTracker(10));

    // Reset before copying
    CopyTracker::copyCount = 0;
    DynamicArray<CopyTracker> arr2(arr1);

    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(CopyTracker::copyCount, 2);
    EXPECT_EQ(arr2.get(0).value, 5);
    EXPECT_EQ(arr2.get(1).value, 10);
}
