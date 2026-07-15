#include "hashmap.h"
#include <gtest/gtest.h>
#include <string>

// Test assignment of empty map to empty map
TEST(HashMapAssignmentTest, AssignmentEmptyToEmpty) {
  HashMap<int, std::string> map1(8, 0.5);
  HashMap<int, std::string> map2(16, 0.75);

  map2 = map1;

  EXPECT_EQ(map2.size(), 0);
  EXPECT_TRUE(map2.isEmpty());
  EXPECT_EQ(map2.bucketCount(), 8);
}

// Test assignment with string data
TEST(HashMapAssignmentTest, BeginnerAssignmentNonEmptyToEmpty) {
  HashMap<std::string, std::string> fruits;
  fruits.insert("apple", "red");
  fruits.insert("banana", "yellow");

  HashMap<std::string, std::string> fruitsCopy;
  fruitsCopy = fruits;

  EXPECT_EQ(fruitsCopy.size(), 2);
  std::string color;
  EXPECT_TRUE(fruitsCopy.get("apple", color));
  EXPECT_EQ(color, "red");
  EXPECT_TRUE(fruitsCopy.get("banana", color));
  EXPECT_EQ(color, "yellow");
}

// Test assignment of empty map to non-empty map
TEST(HashMapAssignmentTest, AssignmentEmptyToNonEmpty) {
  HashMap<int, std::string> emptyMap;
  HashMap<int, std::string> nonEmptyMap;
  nonEmptyMap.insert(1, "one");

  nonEmptyMap = emptyMap;

  EXPECT_EQ(nonEmptyMap.size(), 0);
  EXPECT_TRUE(nonEmptyMap.isEmpty());
  EXPECT_FALSE(nonEmptyMap.exists(1));
}

// Test assignment of non-empty map to non-empty map
TEST(HashMapAssignmentTest, AssignmentNonEmptyToNonEmpty) {
  HashMap<int, std::string> map1;
  map1.insert(1, "one");

  HashMap<int, std::string> map2;
  map2.insert(2, "two");
  map2.insert(3, "three");

  map2 = map1;

  EXPECT_EQ(map2.size(), 1);
  std::string val;
  EXPECT_TRUE(map2.get(1, val));
  EXPECT_EQ(val, "one");
  EXPECT_FALSE(map2.exists(2));
  EXPECT_FALSE(map2.exists(3));
}

// Test self-assignment
TEST(HashMapAssignmentTest, AssignmentSelf) {
  HashMap<int, std::string> myMap;
  myMap.insert(42, "answer");

  myMap = myMap;

  EXPECT_EQ(myMap.size(), 1);
  std::string val;
  EXPECT_TRUE(myMap.get(42, val));
  EXPECT_EQ(val, "answer");
}

// Test deep copy behavior on assignment
TEST(HashMapAssignmentTest, AssignmentDeepCopy) {
  HashMap<int, std::string> map1;
  map1.insert(100, "hundred");

  HashMap<int, std::string> map2;
  map2 = map1;

  map2.insert(100, "hundred-updated");
  map2.insert(200, "two-hundred");

  std::string val1;
  EXPECT_TRUE(map1.get(100, val1));
  EXPECT_EQ(val1, "hundred");
  EXPECT_FALSE(map1.exists(200));

  std::string val2;
  EXPECT_TRUE(map2.get(100, val2));
  EXPECT_EQ(val2, "hundred-updated");
  EXPECT_TRUE(map2.exists(200));
}

// Test self-assignment on an empty map
TEST(HashMapAssignmentTest, AssignmentToSelfEmpty) {
  HashMap<int, std::string> emptyMap;
  emptyMap = emptyMap;
  EXPECT_TRUE(emptyMap.isEmpty());
  EXPECT_EQ(emptyMap.size(), 0);
}
