cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# t04_reactive_and_asynchronous
add_executable(t04_reactive_and_asynchronous_behaviors
    t04_reactive_and_asynchronous_behaviors.cpp
    ${ACTION_NODE_DIR}/say_something_node.hpp
    ${ACTION_NODE_DIR}/move_base_node.hpp
)
target_link_libraries(t04_reactive_and_asynchronous_behaviors
    ${LIBRARY_DIR}/libbehaviortree_cpp.so
)