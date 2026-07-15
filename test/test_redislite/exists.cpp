#include "redislite.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

// Test 1: Exists true
TEST(RedisLiteExistsTest, ExistsTrue) {
  RedisLite redis;
  redis.processCommand("SET mykey myval");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("EXISTS mykey"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "true\n");
}

// Test 2: Exists false
TEST(RedisLiteExistsTest, ExistsFalse) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("EXISTS missingkey"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "false\n");
}

// Test 3: Exists spaces in key
TEST(RedisLiteExistsTest, ExistsSpacesInKey) {
  RedisLite redis;
  redis.processCommand("SET \"my key\" val");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("EXISTS \"my key\""));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "true\n");
}

// Test 4: Exists syntax error missing key
TEST(RedisLiteExistsTest, ExistsSyntaxErrorMissingKey) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("EXISTS"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: EXISTS requires a key\n");
}

// Test 5: Exists syntax error extra arguments
TEST(RedisLiteExistsTest, ExistsSyntaxErrorExtraArgs) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("EXISTS key extra"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: EXISTS requires a key\n");
}
