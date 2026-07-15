#include "redislite.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

// Test 1: Del existing key
TEST(RedisLiteDelTest, DelExisting) {
  RedisLite redis;
  redis.processCommand("SET mykey myval");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("DEL mykey"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "OK\n");

  std::string val;
  EXPECT_FALSE(redis.get("mykey", val));
}

// Test 2: Del non-existing key
TEST(RedisLiteDelTest, DelNonExisting) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("DEL missingkey"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: Key not found\n");
}

// Test 3: Del spaces in key
TEST(RedisLiteDelTest, DelSpacesInKey) {
  RedisLite redis;
  redis.processCommand("SET \"my key\" val");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("DEL \"my key\""));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "OK\n");

  std::string val;
  EXPECT_FALSE(redis.get("my key", val));
}

// Test 4: Del syntax error missing key
TEST(RedisLiteDelTest, DelSyntaxErrorMissingKey) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("DEL"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: DEL requires a key\n");
}

// Test 5: Del syntax error extra arguments
TEST(RedisLiteDelTest, DelSyntaxErrorExtraArgs) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("DEL key extra"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: DEL requires a key\n");
}
