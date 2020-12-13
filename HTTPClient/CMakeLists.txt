cmake_minimum_required(VERSION 3.5)
project(HTTPClient)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_package(Boost 1.71 REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(server ${sources})

target_link_libraries(server
            ${CMAKE_THREAD_LIBS_INIT}
        )
