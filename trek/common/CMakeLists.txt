cmake_minimum_required (VERSION 3.0)
project(trekcommon CXX)

add_definitions(${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic)

set(SOURCES
    applog.cpp
    threadmanager.cpp
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
)

add_library(${PROJECT_NAME} SHARED  ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/common)
