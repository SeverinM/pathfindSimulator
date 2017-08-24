cmake_minimum_required(VERSION 2.6)

project(PathfindSimulator)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(SFML 2 REQUIRED graphics window system)

include_directories(include/)
include_directories(${SFML_INCLUDE_DIR})

file(GLOB_RECURSE
    Source_files
    src/*.cpp
)

file(GLOB_RECURSE
    Header_files
    include/*.hpp
)

add_executable(${PROJECT_NAME} ${Source_files} ${Header_files})
target_link_libraries(PathfindSimulator ${SFML_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)