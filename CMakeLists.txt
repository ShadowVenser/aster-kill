cmake_minimum_required(VERSION 3.31)
project(ecs-demo
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(dependencies)
add_subdirectory(src)

file(COPY
    assets
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)
file(COPY
    config.json
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)