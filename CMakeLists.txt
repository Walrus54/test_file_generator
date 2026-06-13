cmake_minimum_required( VERSION 3.12 )

project( code_generator LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_executable( code_generator main.cpp )
target_include_directories( code_generator PRIVATE include )
