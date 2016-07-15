cmake_minimum_required(VERSION 3.0)
project(treknet CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    multicastsender.cpp
    multicastreceiver.cpp
    controller.cpp
    request.cpp
    response.cpp
    server.cpp
    session.cpp
)

set(HEADERS
    multicastsender.hpp
    multicastreceiver.hpp
    controller.hpp
    controller.hpp
    request.hpp
    response.hpp
    server.hpp
    session.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

find_package(
        Boost
	1.55.0
	REQUIRED
)
include_directories(${Boost_INCLUDE_DIRS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/net)
