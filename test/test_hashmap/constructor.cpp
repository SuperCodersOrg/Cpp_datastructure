#include "hashmap.h"
#include <gtest/gtest.h>
#include <string>

// Test default constructor
TEST(HashMapConstructorTest, DefaultConstructor) {
  HashMap<int, std::string> myMap;

  EXPECT_EQ(myMap.size(), 0);
  EXPECT_TRUE(myMap.isEmpty());
  EXPECT_EQ(myMap.bucketCount(), 16);
  EXPECT_DOUBLE_EQ(myMap.loadFactor(), 0.0);
}

// Test custom constructor
TEST(HashMapConstructorTest, CustomConstructor) {
  HashMap<int, std::string> myMap(8, 0.5);

  EXPECT_EQ(myMap.size(), 0);
  EXPECT_TRUE(myMap.isEmpty());
  EXPECT_EQ(myMap.bucketCount(), 8);
}

// Test custom constructor with invalid arguments
TEST(HashMapConstructorTest, CustomConstructorInvalidArgs) {
  HashMap<int, std::string> myMap1(0, -0.5);
  EXPECT_EQ(myMap1.bucketCount(), 16);

  HashMap<int, std::string> myMap2(-10, 1.5);
  EXPECT_EQ(myMap2.bucketCount(), 16);
}

// Test copy constructor on empty map
TEST(HashMapConstructorTest, CopyConstructorEmpty) {
  HashMap<int, std::string> firstMap(8, 0.5);
  HashMap<int, std::string> secondMap(firstMap);

  EXPECT_EQ(secondMap.size(), 0);
  EXPECT_TRUE(secondMap.isEmpty());
  EXPECT_EQ(secondMap.bucketCount(), 8);
}

// Test copy constructor with string keys/values
TEST(HashMapConstructorTest, BeginnerCopyConstructor) {
  HashMap<std::string, std::string> originalMap;
  originalMap.insert("apple", "red");
  originalMap.insert("banana", "yellow");

  HashMap<std::string, std::string> copiedMap(originalMap);

  EXPECT_EQ(copiedMap.size(), 2);
  EXPECT_FALSE(copiedMap.isEmpty());

  std::string color;
  EXPECT_TRUE(copiedMap.get("apple", color));
  EXPECT_EQ(color, "red");
  EXPECT_TRUE(copiedMap.get("banana", color));
  EXPECT_EQ(color, "yellow");
}

// Test deep copy behavior
TEST(HashMapConstructorTest, CopyConstructorDeepCopy) {
  HashMap<int, std::string> map1;
  map1.insert(10, "ten");

  HashMap<int, std::string> map2(map1);

  // Modify map2 and check that map1 is unchanged
  map2.insert(10, "ten-updated");
  map2.insert(20, "twenty");

  std::string value;
  EXPECT_TRUE(map1.get(10, value));
  EXPECT_EQ(value, "ten");
  EXPECT_FALSE(map1.exists(20));

  EXPECT_TRUE(map2.get(10, value));
  EXPECT_EQ(value, "ten-updated");
  EXPECT_TRUE(map2.exists(20));
}

// Test copy constructor with a larger map
TEST(HashMapConstructorTest, CopyConstructorLargeMap) {
  HashMap<int, int> original;
  for (int i = 0; i < 50; ++i) {
    original.insert(i, i * 10);
  }
  HashMap<int, int> copy(original);
  EXPECT_EQ(copy.size(), 50);
  for (int i = 0; i < 50; ++i) {
    int val = 0;
    EXPECT_TRUE(copy.get(i, val));
    EXPECT_EQ(val, i * 10);
  }
}
