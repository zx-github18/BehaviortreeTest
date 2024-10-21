cmake_minimum_required(VERSION 3.5)
project(behaviortree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_SOURCE_DIR}/src/action_node
    ${PROJECT_SOURCE_DIR}/src/action_condition
)
aux_source_directory(
    ${PROJECT_SOURCE_DIR}/src SRC_LIST
)

# ex01_wrap_legacy
add_executable(ex01_wrap_legacy 
    ${PROJECT_SOURCE_DIR}/src/ex01_wrap_legacy.cpp
)
target_link_libraries(ex01_wrap_legacy 
    ${PROJECT_SOURCE_DIR}/lib/libbehaviortree_cpp.so
)

# t01_first_behaviortree
add_executable(t01_first_behaviortree
    ${PROJECT_SOURCE_DIR}/src/t01_first_behaviortree.cpp
    ${PROJECT_SOURCE_DIR}/src/action_node/approach_object_node.hpp
)
target_link_libraries(t01_first_behaviortree
    ${PROJECT_SOURCE_DIR}/lib/libbehaviortree_cpp.so
)

# t02_blackboard_and_ports
add_executable(t02_blackboard_and_ports
    ${PROJECT_SOURCE_DIR}/src/t02_blackboard_and_ports.cpp
    ${PROJECT_SOURCE_DIR}/src/action_node/say_something_node.hpp
    ${PROJECT_SOURCE_DIR}/src/action_node/think_what_to_say_node.hpp
)
target_link_libraries(t02_blackboard_and_ports
    ${PROJECT_SOURCE_DIR}/lib/libbehaviortree_cpp.so
)

# t03_ports_with_generic_types
add_executable(t03_ports_with_generic_types
    ${PROJECT_SOURCE_DIR}/src/t03_ports_with_generic_types.cpp
    ${PROJECT_SOURCE_DIR}/src/action_node/calculate_goal_node.hpp
    ${PROJECT_SOURCE_DIR}/src/action_node/print_target_node.hpp
)
target_link_libraries(t03_ports_with_generic_types
    ${PROJECT_SOURCE_DIR}/lib/libbehaviortree_cpp.so
)

# t04_reactive_and_asynchronous
add_executable(t04_reactive_and_asynchronous_behaviors
    ${PROJECT_SOURCE_DIR}/src/t04_reactive_and_asynchronous_behaviors.cpp
    ${PROJECT_SOURCE_DIR}/src/action_node/say_something_node.hpp
    ${PROJECT_SOURCE_DIR}/src/action_node/move_base_node.hpp
)
target_link_libraries(t04_reactive_and_asynchronous_behaviors
    ${PROJECT_SOURCE_DIR}/lib/libbehaviortree_cpp.so
)

# t05_using_subtree
add_executable(t05_using_subtree
    ${PROJECT_SOURCE_DIR}/src/t05_using_subtree.cpp
)
target_link_libraries(t05_using_subtree
    ${PROJECT_SOURCE_DIR}/lib/libbehaviortree_cpp.so
)