set(AuspiciousLibrary_TESTS
    "${CMAKE_CURRENT_SOURCE_DIR}/test_to_string.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_cu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_cu_containers.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_sm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_aec.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_0.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_4.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_5.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_6.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_7.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_8.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_9.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_10.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_11.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_ap/test_ap_12.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_fu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tester.cpp")

add_executable(tester ${AuspiciousLibrary_TESTS})
target_include_directories(tester PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/test_ap")
target_link_libraries(tester PRIVATE auspicious_library)

add_custom_command(
    TARGET tester POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/test_fu_read_all_file.txt" "${CMAKE_CURRENT_BINARY_DIR}/test_fu_read_all_file.txt"
)
