cmake_minimum_required(VERSION 3.15)
project(CppDataStructures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

# Main executable
add_executable(simple
    main.cpp
    
)


# GoogleTest
enable_testing()

find_package(GTest REQUIRED)

add_executable(runTests
    test/test_main.cpp
    test/test_dynamicarray/constructor.cpp
    test/test_dynamicarray/assignment.cpp
    test/test_dynamicarray/append.cpp
    test/test_dynamicarray/remove.cpp
    test/test_dynamicarray/insert.cpp
    test/test_dynamicarray/get.cpp
    test/test_dynamicarray/size.cpp
    test/test_dynamicarray/capacity.cpp
    test/test_dynamicarray/isEmpty.cpp
    test/test_dynamicarray/clear.cpp
    test/test_dynamicarray/destructor.cpp
    test/test_linkedlist/constructor.cpp
    test/test_linkedlist/assignment.cpp
    test/test_linkedlist/destructor.cpp
    test/test_linkedlist/insertFront.cpp
    test/test_linkedlist/insertBack.cpp
    test/test_linkedlist/insertAt.cpp
    test/test_linkedlist/deleteFront.cpp
    test/test_linkedlist/deleteBack.cpp
    test/test_linkedlist/deleteAt.cpp
    test/test_linkedlist/search.cpp
    test/test_linkedlist/get.cpp
    test/test_linkedlist/set.cpp
    test/test_linkedlist/size.cpp
    test/test_linkedlist/isEmpty.cpp
    test/test_linkedlist/clear.cpp
    test/test_hashmap/constructor.cpp
    test/test_hashmap/assignment.cpp
    test/test_hashmap/insert.cpp
    test/test_hashmap/get.cpp
    test/test_hashmap/remove.cpp
    test/test_hashmap/clear.cpp
    test/test_hashmap/print.cpp
    test/test_redislite/tokenize.cpp
    test/test_redislite/set.cpp
    test/test_redislite/get.cpp
    test/test_redislite/del.cpp
    test/test_redislite/exists.cpp
    test/test_redislite/clear.cpp
    test/test_redislite/count.cpp
)

target_include_directories(runTests PRIVATE include)

target_link_libraries(runTests
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)