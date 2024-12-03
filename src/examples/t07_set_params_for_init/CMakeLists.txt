cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# t07_set_params_for_init_tree
add_executable(t07_set_params_for_init_tree
    t07_set_params_for_init.cpp
    ${ACTION_NODE_DIR}/say_something_node.hpp
    ${ACTION_NODE_DIR}/move_base_node.hpp
    ${ACTION_NODE_DIR}/action_command_node.hpp
)
target_link_libraries(t07_set_params_for_init_tree
    ${LIBRARY_DIR}/libbehaviortree_cpp.so
)