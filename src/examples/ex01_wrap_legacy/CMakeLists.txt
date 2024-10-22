cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ex01_wrap_legacy
add_executable(ex01_wrap_legacy 
    ex01_wrap_legacy.cpp
)

target_link_libraries(ex01_wrap_legacy 
    ${LIBRARY_DIR}/libbehaviortree_cpp.so
)