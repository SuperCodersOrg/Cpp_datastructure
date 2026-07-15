#include "linkedlist.h"
#include <gtest/gtest.h>

namespace {
class TestObject {
public:
  static int destroyed;
  int val;
  TestObject(int v) : val(v) {}
  TestObject(const TestObject &other) : val(other.val) {}
  ~TestObject() { destroyed++; }
};
int TestObject::destroyed = 0;
}


// Test 1: Destructor destroys all elements in the list
TEST(LinkedListDestructorTest, DestructorDestroysElements) {
  TestObject::destroyed = 0;
  {
    LinkedList<TestObject> list;
    list.insertBack(TestObject(1));
    list.insertBack(TestObject(2));

    // Reset before scope end to ignore temporary objects
    TestObject::destroyed = 0;
  }
  EXPECT_EQ(TestObject::destroyed, 2);
}

// Test 2: clear() destroys all elements
TEST(LinkedListDestructorTest, ClearDestroysAllElements) {
  TestObject::destroyed = 0;
  LinkedList<TestObject> list;
  list.insertBack(TestObject(1));
  list.insertBack(TestObject(2));

  TestObject::destroyed = 0;
  list.clear();
  EXPECT_EQ(TestObject::destroyed, 2);
}

// Test 3: Deletions destroy the removed element
TEST(LinkedListDestructorTest, DeletionDestroysRemovedElement) {
  TestObject::destroyed = 0;
  LinkedList<TestObject> list;
  list.insertBack(TestObject(1));
  list.insertBack(TestObject(2));
  list.insertBack(TestObject(3));

  // Reset before deleting
  TestObject::destroyed = 0;
  list.deleteFront(); // deletes 1
  EXPECT_EQ(TestObject::destroyed, 1);

  TestObject::destroyed = 0;
  list.deleteBack(); // deletes 3
  EXPECT_EQ(TestObject::destroyed, 1);

  TestObject::destroyed = 0;
  list.deleteAt(0); // deletes 2
  EXPECT_EQ(TestObject::destroyed, 1);
}

// Test 4: Destructing an empty list does not cause errors or leaks
TEST(LinkedListDestructorTest, DestructEmptyList) {
  TestObject::destroyed = 0;
  {
    LinkedList<TestObject> list;
  }
  EXPECT_EQ(TestObject::destroyed, 0);
}
