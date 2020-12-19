cmake_minimum_required(VERSION 3.5)
project(ComRedClient)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-Wall")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(HTTPClient)
add_subdirectory(Application)

