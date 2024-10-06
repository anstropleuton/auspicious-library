# Collect all example source files
file(GLOB_RECURSE EXAMPLE_SOURCES CONFIGURE_DEPENDS *.cpp)

foreach(example_src IN LISTS EXAMPLE_SOURCES)
    get_filename_component(example_name ${example_src} NAME_WE)
    add_executable(${example_name} ${example_src})
    
    target_link_libraries(${example_name}
        PRIVATE auspicious_library::auspicious_library
    )
    
    target_compile_options(${example_name} PRIVATE
        $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -g>
        $<$<CONFIG:Release>:-Wall -Wextra -Wpedantic -O3>
    )
    
    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    )
endforeach()
