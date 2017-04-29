cmake_minimum_required(VERSION 3.7)
project(Inference_Engine)

set(CMAKE_CXX_STANDARD 14)

include(${PROJECT_SOURCE_DIR}/CMake/AddSource.cmake)

# Access the global source list of files added via the add_sources() function
get_property(SRC GLOBAL PROPERTY SOURCE_LIST)

add_subdirectory(Source)

add_executable(${PROJECT_NAME} "${SRC}")
target_include_directories(${PROJECT_NAME} PRIVATE Source)