#include "redislite.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

// Test 1: Set success
TEST(RedisLiteSetTest, SetSuccess) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("SET mykey myval"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "OK\n");

  std::string val;
  EXPECT_TRUE(redis.get("mykey", val));
  EXPECT_EQ(val, "myval");
}

// Test 2: Set spaces in value
TEST(RedisLiteSetTest, SetSpacesInValue) {
  RedisLite redis;
  EXPECT_TRUE(redis.processCommand("SET mykey \"hello space world\""));

  std::string val;
  EXPECT_TRUE(redis.get("mykey", val));
  EXPECT_EQ(val, "hello space world");
}

// Test 3: Set update
TEST(RedisLiteSetTest, SetUpdate) {
  RedisLite redis;
  redis.processCommand("SET key val1");
  redis.processCommand("SET key val2");

  std::string val;
  EXPECT_TRUE(redis.get("key", val));
  EXPECT_EQ(val, "val2");
}

// Test 4: Set syntax error missing value
TEST(RedisLiteSetTest, SetSyntaxErrorMissingValue) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("SET mykey"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: SET requires a key and a value\n");

  std::string val;
  EXPECT_FALSE(redis.get("mykey", val));
}

// Test 5: Set syntax error extra arguments
TEST(RedisLiteSetTest, SetSyntaxErrorExtraArgs) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("SET mykey val1 extra"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: SET requires a key and a value\n");
}
