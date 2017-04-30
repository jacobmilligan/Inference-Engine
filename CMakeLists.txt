cmake_minimum_required(VERSION 3.7)
project(iengine)

set(CMAKE_CXX_STANDARD 14)

include(${PROJECT_SOURCE_DIR}/CMake/AddSource.cmake)

include_directories(${PROJECT_SOURCE_DIR}/Source)
include_directories(${PROJECT_SOURCE_DIR}/Deps)

add_subdirectory(${PROJECT_SOURCE_DIR}/Source)
add_subdirectory(${PROJECT_SOURCE_DIR}/Deps/Path)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests)

# Access the global source list of files added via the add_sources() function
get_property(SRC GLOBAL PROPERTY SOURCE_LIST)

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/Source/InferenceEngine/Main.cpp
        "${SRC}")
target_link_libraries(${PROJECT_NAME} skyrocket_path)

# Build static library for testing
add_library(InferenceLib "${SRC}")