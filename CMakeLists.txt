cmake_minimum_required(VERSION 3.30)

project(AuspiciousLibrary
    VERSION 0.0.0.1
    DESCRIPTION "Auspicious Library is a collection of utils for Anstro Pleuton's programs."
    HOMEPAGE_URL "https://anstropleuton.github.io/auspicious-library/"
    LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build Auspicious Library as shared library" OFF)
option(BUILD_EXAMPLES "Build Auspicious Library usage examples" OFF)
option(BUILD_TESTS "Build Auspicious Library tests" OFF)

set(AuspiciousLibrary_gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(AuspiciousLibrary_msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/auspicious_library_config.hpp.in" auspicious_library_config.hpp)

add_library(AuspiciousLibrary_compiler_flags INTERFACE)
target_include_directories(AuspiciousLibrary_compiler_flags INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_features(AuspiciousLibrary_compiler_flags INTERFACE cxx_std_23)

set(AuspiciousLibrary_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/argument_parser.cpp")

add_library(auspicious_library ${AuspiciousLibrary_SOURCES})
target_link_libraries(auspicious_library PUBLIC AuspiciousLibrary_compiler_flags)
target_compile_options(auspicious_library PRIVATE
    $<${AuspiciousLibrary_gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2>
    $<${AuspiciousLibrary_msvc_cxx}:-W3> # I don't know what I am doing with MSVC
)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
