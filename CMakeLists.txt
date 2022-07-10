cmake_minimum_required(VERSION 3.9)

project(uvm_in_cpp VERSION 0.0.1 DESCRIPTION "UVM in CPP")

# required for unit testing using CMake's ctest command
include(CTest)
enable_testing()

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include_directories(${PROJECT_SOURCE_DIR}/src)

# we add the sub-directories that we want CMake to scan
add_subdirectory(src)
add_subdirectory(test)

