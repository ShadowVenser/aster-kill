cmake_minimum_required(VERSION 3.31)
project(ecs-demo
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    
add_subdirectory(dependencies)
add_subdirectory(src)