cmake_minimum_required(VERSION 3.16)

project(SHA_LIB)

FILE(GLOB SHA_HEADERS src/*.h)
FILE(GLOB SHA_SOURCES src/*.cpp)

add_library(SHA_LIB STATIC ${SHA_HEADERS} ${SHA_SOURCES})