project("Skyrocket Path")

set(LIB_NAME skyrocket_path)

set(SRC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Path.cpp)

if (UNIX AND NOT APPLE)
    MESSAGE(STATUS "Skyrocket: Compiling for Linux")
    set(SRC_FILES ${SRC_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/LinuxPath.cpp)
endif ()

if (APPLE)
    MESSAGE(STATUS "Skyrocket: Compiling for macOS")
    set(SRC_FILES ${SRC_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/MacPath.cpp)
endif()

if (WIN32)
    MESSAGE(STATUS "Skyrocket: Compiling for WIN32")
    set(SRC_FILES ${SRC_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/WinPath.cpp)
endif ()

add_library(${LIB_NAME} STATIC ${SRC_FILES})
include_directories(${Lib_NAME} ${CMAKE_CURRENT_SOURCE_DIR})

set(SKYROCKET_PATH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
