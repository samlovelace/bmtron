cmake_minimum_required(VERSION 3.8)
project(bmtron)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include
)

set(BMTRON_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Segment.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/Snake.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AI.cpp
)

add_executable(${PROJECT_NAME} ${BMTRON_SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)