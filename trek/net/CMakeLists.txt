cmake_minimum_required(VERSION 3.0)
project(treknet CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")
include_directories($ {CMAKE_SOURCE_DIR})

set(SOURCES
    controller.cpp
    request.cpp
    response.cpp
    server.cpp
    session.cpp
   )

set(HEADERS
    controller.hpp
    controller.hpp
    request.hpp
    response.hpp
    server.hpp
    session.hpp
   )

add_library($ {PROJECT_NAME} STATIC $ {SOURCES} $ {HEADERS})

install(TARGETS $ {PROJECT_NAME} DESTINATION lib)
install(FILES $ {HEADERS} DESTINATION include / trek / net)
