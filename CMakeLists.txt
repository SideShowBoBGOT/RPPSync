cmake_minimum_required(VERSION 3.18)
project(RwLock
    VERSION 0.0.1
    DESCRIPTION "Implementation of Rust's std::sync::RwLock into C++"
    LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} INTERFACE)
add_library(RwLock::RwLock ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE Include)

add_subdirectory(Examples)
