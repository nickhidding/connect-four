cmake_minimum_required(VERSION 3.10)

# Locate GTest
set(GTEST_DIR ../googletest)
add_subdirectory(${GTEST_DIR}/googletest
                 ${GTEST_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# find_package(GTest REQUIRED)
message(STATUS "dirs ${GTEST_INCLUDE_DIRS}")
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp)
target_link_libraries(runTests gtest_main)
