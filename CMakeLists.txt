cmake_minimum_required(VERSION 3.16)

project(SHA_LIB)

FILE(GLOB SHA_HEADERS sha/*.h)
FILE(GLOB SHA_SOURCES sha/SHA*.cpp)

add_library(SHA_LIB STATIC ${SHA_HEADERS} ${SHA_SOURCES})

add_executable(example sha/example.cpp)
target_link_libraries(example SHA_LIB)