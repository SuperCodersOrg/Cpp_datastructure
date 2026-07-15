#include "hashmap.h"
#include <gtest/gtest.h>
#include <string>

// Test remove of existing key
TEST(HashMapRemoveTest, RemoveExistingKey) {
  HashMap<int, std::string> myMap;
  myMap.insert(1, "one");
  myMap.insert(2, "two");

  EXPECT_EQ(myMap.size(), 2);
  
  myMap.remove(1);

  EXPECT_EQ(myMap.size(), 1);
  EXPECT_FALSE(myMap.exists(1));
  EXPECT_TRUE(myMap.exists(2));
}

// Test remove of non-existing key
TEST(HashMapRemoveTest, RemoveNonExistingKey) {
  HashMap<int, std::string> myMap;
  myMap.insert(1, "one");

  EXPECT_EQ(myMap.size(), 1);
  
  myMap.remove(2);

  EXPECT_EQ(myMap.size(), 1);
  EXPECT_TRUE(myMap.exists(1));
}

// Custom hash that forces collisions
namespace {
struct BeginnerConstantHash {
  size_t operator()(const int &) const {
    return 13;
  }
};
}

// Test remove of colliding key (middle of chain)
TEST(HashMapRemoveTest, RemoveCollidingKey) {
  HashMap<int, std::string, BeginnerConstantHash> myMap;
  myMap.insert(1, "one");
  myMap.insert(2, "two");
  myMap.insert(3, "three");

  EXPECT_EQ(myMap.size(), 3);
  
  myMap.remove(2); // Remove middle node

  EXPECT_EQ(myMap.size(), 2);
  EXPECT_TRUE(myMap.exists(1));
  EXPECT_FALSE(myMap.exists(2));
  EXPECT_TRUE(myMap.exists(3));
}

// Test remove of all keys one by one
TEST(HashMapRemoveTest, RemoveAllKeys) {
  HashMap<int, std::string> myMap;
  myMap.insert(1, "one");
  myMap.insert(2, "two");
  myMap.insert(3, "three");

  myMap.remove(1);
  myMap.remove(2);
  myMap.remove(3);

  EXPECT_EQ(myMap.size(), 0);
  EXPECT_TRUE(myMap.isEmpty());
}

// Test remove with string keys
TEST(HashMapRemoveTest, BeginnerStringRemove) {
  HashMap<std::string, std::string> colors;
  colors.insert("sky", "blue");
  colors.insert("grass", "green");

  colors.remove("sky");
  EXPECT_EQ(colors.size(), 1);
  EXPECT_FALSE(colors.exists("sky"));
  EXPECT_TRUE(colors.exists("grass"));
}

// Test remove of first and last elements in a collision chain
TEST(HashMapRemoveTest, RemoveFirstAndLastInBucket) {
  HashMap<int, std::string, BeginnerConstantHash> myMap;
  myMap.insert(1, "one");   // Tail
  myMap.insert(2, "two");   // Middle
  myMap.insert(3, "three"); // Head

  // Remove head of collision list
  myMap.remove(3);
  EXPECT_FALSE(myMap.exists(3));
  EXPECT_TRUE(myMap.exists(2));
  EXPECT_TRUE(myMap.exists(1));

  // Remove tail of collision list
  myMap.remove(1);
  EXPECT_FALSE(myMap.exists(1));
  EXPECT_TRUE(myMap.exists(2));
}

// Test remove on an empty map
TEST(HashMapRemoveTest, RemoveOnEmptyMap) {
  HashMap<int, std::string> myMap;
  EXPECT_NO_THROW(myMap.remove(42));
  EXPECT_EQ(myMap.size(), 0);
}
