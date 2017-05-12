set(EXE_NAME InferenceTests)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Parser tests config
set(PARSER_TESTS_NAME parser_tests)
add_executable(${PARSER_TESTS_NAME} ParserTests.cpp TruthTableTests.cpp)
target_link_libraries(${PARSER_TESTS_NAME} InferenceLib)
target_link_libraries(${PARSER_TESTS_NAME} skyrocket_path)
target_include_directories(${PARSER_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Deps)
target_include_directories(${PARSER_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Source)

# Visitor tests config
set(VISITOR_TESTS_NAME visitor_tests)
add_executable(${VISITOR_TESTS_NAME} VisitorTests.cpp)
target_link_libraries(${VISITOR_TESTS_NAME} InferenceLib)
target_link_libraries(${VISITOR_TESTS_NAME} skyrocket_path)
target_include_directories(${VISITOR_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Deps)
target_include_directories(${VISITOR_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Source)

# Visitor tests config
set(TRUTHTABLE_TESTS_NAME truth_table_tests)
add_executable(${TRUTHTABLE_TESTS_NAME} TruthTableTests.cpp)
target_link_libraries(${TRUTHTABLE_TESTS_NAME} InferenceLib)
target_link_libraries(${TRUTHTABLE_TESTS_NAME} skyrocket_path)
target_include_directories(${TRUTHTABLE_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Deps)
target_include_directories(${TRUTHTABLE_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Source)

# FC Tests config
set(FC_TESTS_NAME fc_tests)
add_executable(${FC_TESTS_NAME} FCTests.cpp)
target_link_libraries(${FC_TESTS_NAME} InferenceLib)
target_link_libraries(${FC_TESTS_NAME} skyrocket_path)
target_include_directories(${FC_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Deps)
target_include_directories(${FC_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Source)

# KB Tests config
set(KB_TESTS_NAME kb_tests)
add_executable(${KB_TESTS_NAME} KBTests.cpp)
target_link_libraries(${KB_TESTS_NAME} InferenceLib)
target_link_libraries(${KB_TESTS_NAME} skyrocket_path)
target_include_directories(${KB_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Deps)
target_include_directories(${KB_TESTS_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Source)

