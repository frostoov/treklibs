cmake_minimum_required (VERSION 3.0)
project(trekutils CXX)

add_definitions(${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic -fPIC)
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
