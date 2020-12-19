cmake_minimum_required(VERSION 3.5)
project(Application)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_package(Boost 1.71 REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})

add_library(Application STATIC ${sources})
target_include_directories(Application PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(app.out app.cpp)
target_link_libraries(app.out Application HTTPClient -pthread)

