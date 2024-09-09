cmake_minimum_required(VERSION 3.22.0)
project(hash_table_words VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hash_table_words main.cpp HashTable.cpp FileParser.cpp)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_executable(
  HashMap_Test
  HashTable.cpp
  HashMap_Test.cpp
)
target_link_libraries(
    HashMap_Test
    GTest::gtest_main
)
target_include_directories(HashMap_Test INTERFACE ./)
include(GoogleTest)
gtest_discover_tests(HashMap_Test)