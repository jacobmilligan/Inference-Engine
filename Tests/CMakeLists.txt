set(EXE_NAME InferenceTests)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        ParserTests.cpp)

add_executable(${EXE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXE_NAME} InferenceLib)
target_link_libraries(${EXE_NAME} skyrocket_path)

target_include_directories(${EXE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Deps)
target_include_directories(${EXE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Source)
