cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# t06_remapping_ports_of_subtree
add_executable(t06_remapping_ports_of_subtree
    t06_remapping_ports_of_subtree.cpp
    ${ACTION_NODE_DIR}/say_something_node.hpp
    ${ACTION_NODE_DIR}/move_base_node.hpp
)
target_link_libraries(t06_remapping_ports_of_subtree
    ${LIBRARY_DIR}/libbehaviortree_cpp.so
)