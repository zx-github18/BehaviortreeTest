cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# t05_using_subtree
add_executable(t05_using_subtree
    t05_using_subtree.cpp
)
target_link_libraries(t05_using_subtree
    ${LIBRARY_DIR}/libbehaviortree_cpp.so
)