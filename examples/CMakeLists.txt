set(AuspiciousLibrary_EXAMPLES
    "sm/to_string"
    "cu/boundless_containers"
    "cu/enumerated_array"
    "cu/arithmetics"
    "sm/arithmetics")

function(add_example source executable)
    add_executable(${executable} ${source})
    target_link_libraries(${executable} auspicious_library)
endfunction()

foreach(example ${AuspiciousLibrary_EXAMPLES})
    set(example_source "${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp")
    string(REPLACE "/" "_" example_executable ${example})
    add_example(${example_source} ${example_executable})
endforeach()
