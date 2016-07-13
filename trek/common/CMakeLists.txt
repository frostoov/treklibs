cmake_minimum_required(VERSION 3.0)
project(trekcommon CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")


set(HEADERS
    callback.hpp
    stringbuilder.hpp
    serialization.hpp
    timeprint.hpp
    pipe.hpp
)

install(FILES ${HEADERS} DESTINATION include/trek/common)
