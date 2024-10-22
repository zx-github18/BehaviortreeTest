cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../
)

set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/../../lib)
set(ACTION_NODE_DIR ${PROJECT_SOURCE_DIR}/../action_node)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(ex01_wrap_legacy)
add_subdirectory(t01_first_behaviortree)
add_subdirectory(t02_blackboard_and_ports)
add_subdirectory(t03_ports_with_generic_types)
add_subdirectory(t04_reactive_and_asynchronous_behaviors)
add_subdirectory(t05_using_subtree)
add_subdirectory(t06_remapping_ports_of_subtree)