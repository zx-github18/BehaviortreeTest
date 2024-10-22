cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# t02_blackboard_and_ports
add_executable(t02_blackboard_and_ports
    t02_blackboard_and_ports.cpp
    ${ACTION_NODE_DIR}/say_something_node.hpp
    ${ACTION_NODE_DIR}/think_what_to_say_node.hpp
)
target_link_libraries(t02_blackboard_and_ports
    ${LIBRARY_DIR}/libbehaviortree_cpp.so
)