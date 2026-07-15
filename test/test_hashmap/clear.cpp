#include "hashmap.h"
#include <gtest/gtest.h>
#include <string>

// Test clear on empty map
TEST(HashMapClearTest, ClearEmpty) {
  HashMap<int, std::string> myMap;
  EXPECT_EQ(myMap.size(), 0);

  myMap.clear();
  EXPECT_EQ(myMap.size(), 0);
  EXPECT_TRUE(myMap.isEmpty());
}

// Test clear on non-empty map
TEST(HashMapClearTest, ClearNonEmpty) {
  HashMap<int, std::string> myMap;
  myMap.insert(1, "one");
  myMap.insert(2, "two");
  myMap.insert(3, "three");

  EXPECT_EQ(myMap.size(), 3);
  
  myMap.clear();

  EXPECT_EQ(myMap.size(), 0);
  EXPECT_TRUE(myMap.isEmpty());
  EXPECT_FALSE(myMap.exists(1));
  EXPECT_FALSE(myMap.exists(2));
  EXPECT_FALSE(myMap.exists(3));
}

// Test that clear does not modify bucket capacity
TEST(HashMapClearTest, ClearDoesNotChangeBucketCount) {
  HashMap<int, std::string> myMap(8);
  EXPECT_EQ(myMap.bucketCount(), 8);

  myMap.insert(1, "one");
  myMap.clear();

  EXPECT_EQ(myMap.bucketCount(), 8);
}

// Test clear with string keys
TEST(HashMapClearTest, BeginnerStringClear) {
  HashMap<std::string, std::string> userSessions;
  userSessions.insert("user1", "active");
  userSessions.insert("user2", "idle");

  userSessions.clear();
  EXPECT_EQ(userSessions.size(), 0);
  EXPECT_TRUE(userSessions.isEmpty());
}

namespace {
// Helper class to track object destruction
class BeginnerClearObject {
public:
  static int destroyedCount;
  int value;
  BeginnerClearObject(int val) : value(val) {}
  BeginnerClearObject(const BeginnerClearObject &other) : value(other.value) {}
  ~BeginnerClearObject() { destroyedCount++; }
};
int BeginnerClearObject::destroyedCount = 0;
}

// Test that clear properly calls destructors of stored values
TEST(HashMapClearTest, ClearDestroysElements) {
  BeginnerClearObject::destroyedCount = 0;
  {
    HashMap<int, BeginnerClearObject> myMap;
    myMap.insert(1, BeginnerClearObject(100));
    myMap.insert(2, BeginnerClearObject(200));

    // Reset count before clear
    BeginnerClearObject::destroyedCount = 0;

    myMap.clear();

    EXPECT_EQ(BeginnerClearObject::destroyedCount, 2);
  }
}

// Test clear followed by refilling and rehashing
TEST(HashMapClearTest, ClearAndRehashStability) {
  HashMap<int, std::string> myMap(4, 0.5);
  myMap.insert(1, "one");
  myMap.insert(2, "two");
  
  myMap.clear();

  myMap.insert(3, "three");
  myMap.insert(4, "four");
  myMap.insert(5, "five"); // triggers rehash (3 elements > 4 * 0.5 threshold)

  EXPECT_EQ(myMap.bucketCount(), 8);
  EXPECT_EQ(myMap.size(), 3);
  std::string val;
  EXPECT_TRUE(myMap.get(5, val));
  EXPECT_EQ(val, "five");
}

// Test clearing a map with many elements
TEST(HashMapClearTest, ClearLargeMap) {
  HashMap<int, int> myMap;
  for (int i = 0; i < 100; ++i) {
    myMap.insert(i, i);
  }
  myMap.clear();
  EXPECT_TRUE(myMap.isEmpty());
  EXPECT_EQ(myMap.size(), 0);
}
