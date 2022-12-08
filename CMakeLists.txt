cmake_minimum_required(VERSION 3.23)

project(advent-of-code-2022)

# Creating a target for each file found
file(GLOB_RECURSE ADVENT_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
foreach (SOURCE ${ADVENT_SOURCES})
    get_filename_component(TARGET_NAME ${SOURCE} NAME_WE)
    add_executable(${TARGET_NAME} ${SOURCE})
endforeach ()