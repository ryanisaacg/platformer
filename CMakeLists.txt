cmake_minimum_required(VERSION 2.4.0)
cmake_policy(SET CMP0003 NEW)

project (platformer)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SOURCES src/*.cpp)
file(GLOB INCLUDES include/*.h)
add_subdirectory(arcade-physics)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/arcade-physics/include)

add_executable(game ${SOURCES} ${INCLUDES})
set_property(TARGET game PROPERTY CXX_STANDARD 14)
target_link_libraries(game ${SDL2_LIBRARIES})
target_link_libraries(game ${CMAKE_CURRENT_BINARY_DIR}/arcade-physics/libarcade-physics.a)
