cmake_minimum_required(VERSION 3.10)
project(ConnectFour)

# detect operating system and host processor
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

# find GTK3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Include entry point & sources
include_directories("${PROJECT_BINARY_DIR}")
file(GLOB SOURCES *.h *.cpp)
add_executable(ConnectFour main.cpp ${SOURCES})
set_property(TARGET ConnectFour PROPERTY ENABLE_EXPORTS true)

# Include GTK3
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
target_link_libraries(ConnectFour ${CMAKE_THREAD_LIBS_INIT} ${GTK3_LIBRARIES} )
add_definitions(${GTK3_CFLAGS_OTHER})
