cmake_minimum_required(VERSION 3.5)

project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_executable(ex01_wrap_legacy ${SRC_LIST})

target_link_libraries(ex01_wrap_legacy 
    ${PROJECT_SOURCE_DIR}/lib/libbehaviortree_cpp.so
)