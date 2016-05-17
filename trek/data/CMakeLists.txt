cmake_minimum_required(VERSION 3.0)
project(trekdata CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")
include_directories($ {CMAKE_SOURCE_DIR})

set(
    SOURCES
    eventrecord.cpp
    hitrecord.cpp
)

set(
    HEADERS
    nevod.hpp
    eventrecord.hpp
    hitrecord.hpp
)

add_library($ {PROJECT_NAME} STATIC $ {SOURCES})

install(TARGETS $ {PROJECT_NAME} DESTINATION lib)
install(FILES $ {HEADERS} DESTINATION include / trek / data)
