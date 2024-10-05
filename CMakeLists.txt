cmake_minimum_required(VERSION 3.10)

project(auspicious_library VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED "Build shared library" OFF)
option(BUILD_DEBUG "Build debug mode" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)
option(BUILD_TESTS "Build tests" OFF)

include_directories(include)

set(SOURCES
    src/argument_parser.cpp
)

if(BUILD_SHARED)
    add_library(auspicious_library SHARED ${SOURCES})
else()
    add_library(auspicious_library STATIC ${SOURCES})
endif()

if(BUILD_DEBUG)
    target_compile_options(auspicious_library PRIVATE -Wall -g)
else()
    target_compile_options(auspicious_library PRIVATE -Wall -s -O3)
endif()

if(BUILD_EXAMPLES)
    add_executable(sm_to_string examples/sm/to_string.cpp)
    add_executable(cu_boundless_containers examples/cu/boundless_containers.cpp)
    add_executable(cu_enumerated_array examples/cu/enumerated_array.cpp)

    set_target_properties(sm_to_string PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
    set_target_properties(cu_boundless_containers PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
    set_target_properties(cu_enumerated_array PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")

    target_link_libraries(sm_to_string PRIVATE auspicious_library)
    target_link_libraries(cu_boundless_containers PRIVATE auspicious_library)
    target_link_libraries(cu_enumerated_array PRIVATE auspicious_library)

    if(BUILD_DEBUG)
        target_compile_options(sm_to_string PRIVATE -Wall -g)
        target_compile_options(cu_boundless_containers PRIVATE -Wall -g)
        target_compile_options(cu_enumerated_array PRIVATE -Wall -g)
    else()
        target_compile_options(sm_to_string PRIVATE -Wall -s -O3)
        target_compile_options(cu_boundless_containers PRIVATE -Wall -s -O3)
        target_compile_options(cu_enumerated_array PRIVATE -Wall -s -O3)
    endif()
endif()

if(BUILD_TESTS)
    enable_testing()

    set(TEST_SOURCES
        tests/test_to_string.cpp
        tests/test_cu.cpp
        tests/test_cu_containers.cpp
        tests/test_sm.cpp
        tests/test_aec.cpp
        tests/test_ap/test_ap_0.cpp
        tests/test_ap/test_ap_1.cpp
        tests/test_ap/test_ap_2.cpp
        tests/test_ap/test_ap_3.cpp
        tests/test_ap/test_ap_4.cpp
        tests/test_ap/test_ap_5.cpp
        tests/test_ap/test_ap_6.cpp
        tests/test_ap/test_ap_7.cpp
        tests/test_ap/test_ap_8.cpp
        tests/test_ap/test_ap_9.cpp
        tests/test_ap/test_ap_10.cpp
        tests/test_ap/test_ap_11.cpp
        tests/test_ap/test_ap_12.cpp
        tests/test_ap.cpp
        tests/test_fu.cpp
        tests/tester.cpp
    )

    add_executable(tester ${TEST_SOURCES})
    set_target_properties(tester PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

    include_directories(tests)
    include_directories(tests/test_ap)

    if(BUILD_DEBUG)
        target_compile_options(tester PRIVATE -Wall -g)
    else()
        target_compile_options(tester PRIVATE -Wall -s -O3)
    endif()

    target_link_libraries(tester PRIVATE auspicious_library)

    add_custom_command(TARGET tester POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/tests/test_fu_read_all_file.txt
        ${CMAKE_BINARY_DIR}/tests/test_fu_read_all_file.txt
    )

    add_test(NAME run_tester COMMAND tester)
endif()
