cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(${PROJECT_SOURCE_DIR})
# t01_first_behaviortree
add_executable(t01_first_behaviortree 
    t01_first_behaviortree.cpp
    ${ACTION_NODE_DIR}/approach_object_node.hpp
)

target_link_libraries(t01_first_behaviortree
     ${LIBRARY_DIR}/libbehaviortree_cpp.so
)
