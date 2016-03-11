cmake_minimum_required(VERSION 3.0)
project(trekcommon CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(SOURCES
    filesize.cpp
)

set(HEADERS
    callback.hpp
    stringbuilder.hpp
	serialization.hpp
	timeprint.hpp
    filesize.hpp
    pipe.hpp
)

add_library(${PROJECT_NAME} STATIC  ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/common)
