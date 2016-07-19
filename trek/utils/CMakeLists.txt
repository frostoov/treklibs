cmake_minimum_required(VERSION 3.0)
project(trekutils CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    chamber.cpp
    chamberhandler.cpp)

set(HEADERS
    chamberhandler.hpp
    chamber.hpp
    trektypes.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)


install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/utils)
