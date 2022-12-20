cmake_minimum_required(VERSION 3.20)

project(advent-of-code-2022)


# Creating a target for each file found
file(GLOB_RECURSE ADVENT_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
foreach (SOURCE ${ADVENT_SOURCES})
    get_filename_component(TARGET_NUMBER ${SOURCE} NAME_WE)
    string(LENGTH ${TARGET_NUMBER} LENGTH)
    set(TARGET_PREPEND "")
    if(${LENGTH} EQUAL "1")
        set(TARGET_PREPEND "0")
    endif()
    set(TARGET_NAME "${TARGET_PREPEND}${TARGET_NUMBER}")
    add_executable(${TARGET_NAME} ${SOURCE})
    add_executable(${TARGET_NAME}-example ${SOURCE})
    target_compile_definitions(
            ${TARGET_NAME}
            PUBLIC
            "INPUT_FILENAME=\"${CMAKE_CURRENT_SOURCE_DIR}/input/${TARGET_NAME}.txt\""
    )
    target_compile_definitions(
            ${TARGET_NAME}-example
            PUBLIC
            "INPUT_FILENAME=\"${CMAKE_CURRENT_SOURCE_DIR}/input/${TARGET_NAME}_example.txt\""
    )
    set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
endforeach ()