cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# t03_ports_with_generic_types
add_executable(t03_ports_with_generic_types
    t03_ports_with_generic_types.cpp
    ${ACTION_NODE_DIR}/calculate_goal_node.hpp
    ${ACTION_NODE_DIR}/print_target_node.hpp
)
target_link_libraries(t03_ports_with_generic_types
    ${LIBRARY_DIR}/libbehaviortree_cpp.so
)