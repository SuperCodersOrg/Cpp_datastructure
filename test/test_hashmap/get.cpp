#include "hashmap.h"
#include <gtest/gtest.h>
#include <string>

// Test get of existing key
TEST(HashMapGetTest, GetExistingKey) {
  HashMap<int, std::string> myMap;
  myMap.insert(10, "ten");

  std::string val;
  EXPECT_TRUE(myMap.get(10, val));
  EXPECT_EQ(val, "ten");
}

// Test get of non-existing key
TEST(HashMapGetTest, GetNonExistingKey) {
  HashMap<int, std::string> myMap;
  myMap.insert(10, "ten");

  std::string val = "unchanged";
  EXPECT_FALSE(myMap.get(20, val));
  EXPECT_EQ(val, "unchanged");
}

// Test get on const HashMap
TEST(HashMapGetTest, GetConstHashMap) {
  HashMap<int, std::string> myMap;
  myMap.insert(10, "ten");

  const HashMap<int, std::string> constMap(myMap);
  std::string val;
  EXPECT_TRUE(constMap.get(10, val));
  EXPECT_EQ(val, "ten");
}

// Custom hash that forces collisions
namespace {
struct BeginnerConstantHash {
  size_t operator()(const int &) const {
    return 42;
  }
};
}

// Test get with colliding keys
TEST(HashMapGetTest, GetWithCollisions) {
  HashMap<int, std::string, BeginnerConstantHash> myMap;
  myMap.insert(1, "one");
  myMap.insert(2, "two");
  myMap.insert(3, "three");

  std::string val;
  EXPECT_TRUE(myMap.get(1, val));
  EXPECT_EQ(val, "one");

  EXPECT_TRUE(myMap.get(2, val));
  EXPECT_EQ(val, "two");

  EXPECT_TRUE(myMap.get(3, val));
  EXPECT_EQ(val, "three");
}

// Test get with string keys
TEST(HashMapGetTest, BeginnerStringGet) {
  HashMap<std::string, std::string> capitals;
  capitals.insert("France", "Paris");
  capitals.insert("Japan", "Tokyo");

  std::string capital;
  EXPECT_TRUE(capitals.get("Japan", capital));
  EXPECT_EQ(capital, "Tokyo");
  EXPECT_FALSE(capitals.get("Canada", capital));
}

// Test exists method
TEST(HashMapGetTest, ExistsMethod) {
  HashMap<int, std::string> myMap;
  myMap.insert(5, "five");

  EXPECT_TRUE(myMap.exists(5));
  EXPECT_FALSE(myMap.exists(10));
}

// Test get on an empty map
TEST(HashMapGetTest, GetOnEmptyMap) {
  HashMap<int, std::string> emptyMap;
  std::string val = "default";
  EXPECT_FALSE(emptyMap.get(1, val));
  EXPECT_EQ(val, "default");
}
