cmake_minimum_required (VERSION 3.0)
project(trekutils CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic -pipe -march=native")
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
	chamber.cpp
	chamberhandler.cpp
	trekhandler.cpp)

set(HEADERS
	chamberhandler.hpp
	chamber.hpp
	trekhandler.hpp
	trektypes.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/utils)
