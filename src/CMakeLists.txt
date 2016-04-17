set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED graphics window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
elseif(NOT SFML_FOUND)
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

find_package(ZLIB REQUIRED)

if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
elseif(NOT ZLIB_FOUND)
    set(ZLIB_ROOT "" CACHE PATH "zlib top-level directory")
	message("\n-> zlib directory not found. Set ZLIB_ROOT to zlib's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the zlib libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/animatedsprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/animation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/boid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cluster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/largecluster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mediumcluster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mediumenemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/smallenemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/smallcluster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stuffmath.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/triangleship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangleship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/circleship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wavecontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/projectile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/laserprojectile.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} tmx-loader)

target_link_libraries(${PROJECT_NAME} tmx-loader thor ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${ZLIB_LIBRARIES})
