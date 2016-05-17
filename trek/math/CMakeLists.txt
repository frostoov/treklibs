cmake_minimum_required(VERSION 3.0)
project(trekmath CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(
    HEADERS
    histogram.hpp
    coordsystem.hpp
    plane.hpp
    quadrangle2.hpp
    quadrangle3.hpp
    hexahedron.hpp
    general.hpp
    line2.hpp
    line3.hpp
    vec2.hpp
    vec3.hpp
)

set(
    SOURCES
    histogram.cpp
    coordsystem.cpp
    plane.cpp
    quadrangle2.cpp
    quadrangle3.cpp
    hexahedron.cpp
    line2.cpp
    line3.cpp
    vec2.cpp
    vec3.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/math)
