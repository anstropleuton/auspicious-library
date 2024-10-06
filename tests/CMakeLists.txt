# Collect all test source files
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(tester ${TEST_SOURCES})

target_include_directories(tester PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ap
)

target_link_libraries(tester
    PRIVATE auspicious_library::auspicious_library
)

target_compile_options(tester PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -g>
    $<$<CONFIG:Release>:-Wall -Wextra -Wpedantic -O3>
)

set_target_properties(tester PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)

# Ensure the required test data file is copied after build
add_custom_command(TARGET tester POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/tests/test_fu_read_all_file.txt"
        "${CMAKE_BINARY_DIR}/tests/test_fu_read_all_file.txt"
)

# Register the test
add_test(NAME run_tester COMMAND tester)
