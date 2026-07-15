#include "hashmap.h"
#include <gtest/gtest.h>
#include <string>

// Test insert of new keys
TEST(HashMapInsertTest, InsertNewKey) {
  HashMap<int, std::string> myMap;
  
  myMap.insert(1, "one");
  EXPECT_EQ(myMap.size(), 1);
  EXPECT_TRUE(myMap.exists(1));

  myMap.insert(2, "two");
  EXPECT_EQ(myMap.size(), 2);
  EXPECT_TRUE(myMap.exists(2));
}

// Test updating existing keys
TEST(HashMapInsertTest, InsertUpdateKey) {
  HashMap<int, std::string> myMap;
  myMap.insert(1, "one");
  EXPECT_EQ(myMap.size(), 1);

  myMap.insert(1, "one-updated");
  EXPECT_EQ(myMap.size(), 1);

  std::string val;
  EXPECT_TRUE(myMap.get(1, val));
  EXPECT_EQ(val, "one-updated");
}

// Custom hash that forces collisions by returning a constant index
namespace {
struct BeginnerConstantHash {
  size_t operator()(const int &) const {
    return 3;
  }
};
}

// Test handling of colliding keys via chaining
TEST(HashMapInsertTest, InsertCollidingKeys) {
  HashMap<int, std::string, BeginnerConstantHash> myMap(4);

  myMap.insert(1, "one");
  myMap.insert(2, "two");
  myMap.insert(3, "three");

  EXPECT_EQ(myMap.size(), 3);
  EXPECT_EQ(myMap.collisions(), 2);

  std::string val;
  EXPECT_TRUE(myMap.get(1, val));
  EXPECT_EQ(val, "one");
  EXPECT_TRUE(myMap.get(2, val));
  EXPECT_EQ(val, "two");
  EXPECT_TRUE(myMap.get(3, val));
  EXPECT_EQ(val, "three");
}

// Test insert with string keys
TEST(HashMapInsertTest, BeginnerStringKeys) {
  HashMap<std::string, double> priceMap;
  priceMap.insert("milk", 2.50);
  priceMap.insert("bread", 1.99);

  EXPECT_EQ(priceMap.size(), 2);
  double price;
  EXPECT_TRUE(priceMap.get("milk", price));
  EXPECT_DOUBLE_EQ(price, 2.50);
}

// Test if inserting past threshold triggers rehash
TEST(HashMapInsertTest, InsertTriggersRehash) {
  HashMap<int, std::string> myMap(4, 0.5);
  EXPECT_EQ(myMap.bucketCount(), 4);

  myMap.insert(1, "one");
  myMap.insert(2, "two");
  EXPECT_EQ(myMap.bucketCount(), 4);

  // 3rd element triggers rehash since 3/4 = 0.75 > 0.5 threshold
  myMap.insert(3, "three");
  EXPECT_EQ(myMap.bucketCount(), 8);
  EXPECT_EQ(myMap.size(), 3);

  std::string val;
  EXPECT_TRUE(myMap.get(1, val));
  EXPECT_EQ(val, "one");
  EXPECT_TRUE(myMap.get(2, val));
  EXPECT_EQ(val, "two");
  EXPECT_TRUE(myMap.get(3, val));
  EXPECT_EQ(val, "three");
}

// Test inserting large number of elements
TEST(HashMapInsertTest, InsertLargeNumberOfElements) {
  HashMap<int, int> myMap(8, 0.5);
  int totalElements = 100;

  for (int i = 0; i < totalElements; i++) {
    myMap.insert(i, i * 10);
  }

  EXPECT_EQ(myMap.size(), totalElements);
  EXPECT_GT(myMap.bucketCount(), 8);

  for (int i = 0; i < totalElements; i++) {
    int val = 0;
    EXPECT_TRUE(myMap.get(i, val));
    EXPECT_EQ(val, i * 10);
  }
}

// Test insert with empty string as key
TEST(HashMapInsertTest, InsertEmptyStringKey) {
  HashMap<std::string, int> myMap;
  myMap.insert("", 42);
  EXPECT_EQ(myMap.size(), 1);
  int val = 0;
  EXPECT_TRUE(myMap.get("", val));
  EXPECT_EQ(val, 42);
}
