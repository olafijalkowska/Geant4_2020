cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
project(szatanskaGra)

include_directories(include)

set(CMAKE_BUILD_TYPE release)

# User code
file(GLOB sources src/*.cpp)
file(GLOB headers include/*.h)

add_executable(szatanskaGra szatanskaGra.cpp ${sources} ${headers})

