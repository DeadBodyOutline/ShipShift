cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "ld35")

project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)") # XXX Change to Release later

if(CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader/include)
link_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/sfml-tmxloader)

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/thor/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/thor/extlibs/aurora/include)
link_directories(${CMAKE_SOURCE_DIR}/3rdparty/dependencies/thor/src)

add_subdirectory(src)
