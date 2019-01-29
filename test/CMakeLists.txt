cmake_minimum_required(VERSION 3.10)

# Locate GTest
set(GTEST_DIR ../googletest)
#add_subdirectory(${GTEST_DIR}/googletest
#                 ${GTEST_DIR}/googletest-build
#                 EXCLUDE_FROM_ALL)
add_subdirectory(${GTEST_DIR}/googlemock
                 ${GTEST_DIR}/googlemock-build
                 EXCLUDE_FROM_ALL)

# find GTK3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Include sources
set(PROGRAM_DIR ${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROGRAM_DIR})
link_directories(${PROGRAM_DIR})
#add_subdirectory(${PROGRAM_DIR} ${PROGRAM_DIR}/../src-build EXCLUDE_FROM_ALL)
file(GLOB SOURCES ${PROGRAM_DIR}/*.h ${PROGRAM_DIR}/*.cpp)
list(REMOVE_ITEM SOURCES ${PROGRAM_DIR}/main.cpp)

# Link runTests with what we want to test and the GTest and pthread library
enable_testing()
file(GLOB TEST "./*.cc")
message(STATUS "found test sources= ${TEST}")
message(STATUS "found sources= ${SOURCES}")
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
add_executable(runTests tests.cpp ${TEST} ${SOURCES})
target_link_libraries(runTests gtest_main gmock_main)
#target_link_libraries(runTests ConnectFour)

# Include GTK3
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
target_link_libraries(runTests ${CMAKE_THREAD_LIBS_INIT} ${GTK3_LIBRARIES} )
add_definitions(${GTK3_CFLAGS_OTHER})
