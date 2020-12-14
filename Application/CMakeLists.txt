cmake_minimum_required(VERSION 3.5)
project(HTTPClient)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_package(Boost 1.71 REQUIRED)
find_package(Threads)

add_executable(main.out ${sources})

target_link_libraries(main.out
            ${CMAKE_THREAD_LIBS_INIT}
        )
