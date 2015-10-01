cmake_minimum_required (VERSION 3.0)
project(trekcommon CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic -pipe -march=native")

set(SOURCES
    applog.cpp
    threadmanager.cpp
    streamsize.cpp
)

set(HEADERS
	applog.hpp
    assertion.hpp
    callback.hpp
	enumcontainer.hpp
    stringbuilder.hpp
	serialization.hpp
    threadmanager.hpp
	timeprint.hpp
    streamsize.hpp
    pipe.hpp
)

add_library(${PROJECT_NAME} SHARED  ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/common)
