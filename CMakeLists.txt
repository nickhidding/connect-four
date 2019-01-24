cmake_minimum_required(VERSION 3.10)
project(ConnectFour)

# detect operating system and host processor
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(Main main.cpp)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
target_link_libraries(Main ${CMAKE_THREAD_LIBS_INIT} ${GTK3_LIBRARIES} )

add_definitions(${GTK3_CFLAGS_OTHER})
