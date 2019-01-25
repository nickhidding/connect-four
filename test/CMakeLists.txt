cmake_minimum_required(VERSION 3.10)

# Locate GTest
set(GTEST_DIR ../googletest)
add_subdirectory(${GTEST_DIR}/googletest
                 ${GTEST_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Include sources
set(PROGRAM_DIR ${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROGRAM_DIR})
link_directories(${PROGRAM_DIR})
add_subdirectory(${PROGRAM_DIR} ${PROGRAM_DIR}/../src-build EXCLUDE_FROM_ALL)

# Link runTests with what we want to test and the GTest and pthread library
enable_testing()
file(GLOB TEST "./*.cc")
message(STATUS "found sources= ${TEST}")
add_executable(runTests tests.cpp ${TEST})
target_link_libraries(runTests gtest_main)
target_link_libraries(runTests Main)
