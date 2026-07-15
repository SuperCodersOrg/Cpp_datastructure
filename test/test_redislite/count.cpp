#include "redislite.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

// Test 1: Count empty
TEST(RedisLiteCountTest, CountEmpty) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("COUNT"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "0\n");
}

// Test 2: Count multiple keys
TEST(RedisLiteCountTest, CountMultiple) {
  RedisLite redis;
  redis.processCommand("SET k1 v1");
  redis.processCommand("SET k2 v2");
  redis.processCommand("SET k3 v3");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("COUNT"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "3\n");
}

// Test 3: Count after deletion
TEST(RedisLiteCountTest, CountAfterDelete) {
  RedisLite redis;
  redis.processCommand("SET k1 v1");
  redis.processCommand("SET k2 v2");
  redis.processCommand("DEL k1");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("COUNT"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "1\n");
}

// Test 4: Count syntax error extra arguments
TEST(RedisLiteCountTest, CountSyntaxErrorExtraArgs) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("COUNT extra"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: COUNT does not take any arguments\n");
}

// Test 5: Count large state
TEST(RedisLiteCountTest, CountLargeState) {
  RedisLite redis;
  for (int i = 0; i < 50; ++i) {
    redis.processCommand("SET key" + std::to_string(i) + " val");
  }

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("COUNT"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "50\n");
}
