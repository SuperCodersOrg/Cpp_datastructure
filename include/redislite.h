#pragma once

#include <iostream>
#include <string>
#include "hashmap.h"
#include "dynamicarray.h"

class RedisLite
{
public:
    RedisLite();

    void run();

    // Testing interface
    bool processCommand(const std::string& input);
    DynamicArray<std::string> tokenize(const std::string& input) const;
    bool get(const std::string& key, std::string& value);

private:

    HashMap<std::string, std::string> store;

    bool parseInput(const DynamicArray<std::string>& tokens);

    std::string toUpper(std::string str) const;

    void handleSet(const std::string& key,
                   const std::string& value);

    void handleGet(const std::string& key);

    void handleDel(const std::string& key);

    void handleExists(const std::string& key);

    void handleCount();

    void handleClear();

    void printHelp() const;
};

#include "../src/redislite.tpp"