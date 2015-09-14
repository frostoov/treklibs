cmake_minimum_required (VERSION 3.0)
project(trekdata)

add_definitions(${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
	ctudcrecord.cpp
	dataset.cpp
	datasetheader.cpp
	tdcrecord.cpp
	tdcsettings.cpp)
    
set(HEADERS
    ctudcrecord.hpp
    datasetheader.hpp
    dataset.hpp
    structs.hpp
    tdcrecord.hpp
    tdcsettings.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/trek/data)
