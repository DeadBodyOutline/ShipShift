set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/boid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/circleprojectile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mediumenemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/smallenemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/largeenemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stuffmath.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/triangleship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rectangleship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/circleship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wavecontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/projectile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/laserprojectile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timedevent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/guidedprojectile.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

#add_definitions(-DSFML_STATIC)
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
    # static
    target_link_libraries(${PROJECT_NAME} ${SFML_DEPENDENCIES})
endif(SFML_FOUND)
#elseif(NOT SFML_FOUND)
	#set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	#message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	#message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
#endif()





find_package(Thor REQUIRED)
include_directories(${THOR_INCLUDE_DIR})
if (THOR_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} ${THOR_LIBRARY})
endif(THOR_FOUND)

file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_SOURCE_DIR}/build/src)

# installation (check it)
install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION .)
install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION .)

# XXX mac version notes:
#on macos used it to fix freetype path:
#- copied freetype.framework from SFML install into Frameworks; run:
#- install_name_tool -change "@rpath/../Frameworks/freetype.framework/Versions/A/freetype" "@loader_path/./Frameworks/freetype.framework/Versions/A/freetype" ld32
