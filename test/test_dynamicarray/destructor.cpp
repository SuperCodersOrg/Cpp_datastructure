#include "dynamicarray.h"
#include <gtest/gtest.h>

class TestObject {
public:
  static int destroyed;

  TestObject() = default;
  TestObject(const TestObject &) = default;

  ~TestObject() { destroyed++; }
};

int TestObject::destroyed = 0;

TEST(DynamicArrayDestructorTest, DestructorDestroysElements) {
  TestObject::destroyed = 0;

  {
    DynamicArray<TestObject> arr;
    arr.append(TestObject());
    arr.append(TestObject());

    // Ignore temporary objects created during append
    TestObject::destroyed = 0;
  }

  EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(DynamicArrayDestructorTest, ClearDestroysAllElements) {
  TestObject::destroyed = 0;

  DynamicArray<TestObject> arr;
  arr.append(TestObject());
  arr.append(TestObject());

  TestObject::destroyed = 0;

  arr.clear();

  EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(DynamicArrayDestructorTest, RemoveDestroysAnElement) {
  TestObject::destroyed = 0;

  DynamicArray<TestObject> arr;
  arr.append(TestObject());
  arr.append(TestObject());

  TestObject::destroyed = 0;

  arr.remove(0);

  EXPECT_GE(TestObject::destroyed, 1);
}

// Test 4: Verify destructor calls after copy construction
TEST(DynamicArrayDestructorTest, DestructorAfterCopyConstruction) {
  TestObject::destroyed = 0;
  {
    DynamicArray<TestObject> arr1;
    arr1.append(TestObject());
    arr1.append(TestObject());

    TestObject::destroyed = 0;
    {
      DynamicArray<TestObject> arr2(arr1);
      // Wait, copy constructor will construct new elements.
      // Reset tracker before exit of scope
      TestObject::destroyed = 0;
    }
    // arr2 goes out of scope and destroys its 2 elements
    EXPECT_EQ(TestObject::destroyed, 2);
    
    TestObject::destroyed = 0;
  }
  // arr1 goes out of scope and destroys its 2 elements
  EXPECT_EQ(TestObject::destroyed, 2);
}

// Test 5: Verify destructor calls during resize operations
TEST(DynamicArrayDestructorTest, DestructorDuringResize) {
  TestObject::destroyed = 0;
  {
    DynamicArray<TestObject> arr;
    // Initial capacity is 1. Appending second element triggers resize.
    arr.append(TestObject());
    TestObject::destroyed = 0;
    
    arr.append(TestObject()); // triggers resize from 1 to 2
    // During resize, 1 element is copy-constructed to new memory, and the old 1 is destructed.
    // Also, the new element is appended.
    // We expect the old element to have been destructed.
    EXPECT_GE(TestObject::destroyed, 1);
    
    TestObject::destroyed = 0;
  }
  // Scope exit should destroy the 2 elements currently in the array
  EXPECT_EQ(TestObject::destroyed, 2);
}
