set(EXE_NAME InferenceTests)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Skeleton.cpp)

add_executable(${EXE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXE_NAME} STATIC InferenceLib)

target_include_directories(${EXE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Deps/catch)
