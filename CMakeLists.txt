cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

ADD_DEFINITIONS(
    -Wall
    -std=c++11
)

set(PROJECT_NAME "ld35")

project(${PROJECT_NAME})

macro(thor_link_thor THOR_TARGET)
    target_link_libraries(${THOR_TARGET} thor)
endmacro()

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)")

#if(CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#endif()

#if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
#endif()

#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/thor/include)
#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/thor/extlibs/aurora/include)
#link_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/thor/src)

add_subdirectory(src)
