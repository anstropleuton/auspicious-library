cmake_minimum_required(VERSION 3.30)

project(auspicious_library
    VERSION 0.0.1
    DESCRIPTION "Auspicious Library is a collection of utils for Anstro Pleuton's programs."
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)
option(BUILD_TESTS "Build tests" OFF)

# Include GNUInstallDirs for standard installation directories
include(GNUInstallDirs)

# Collect library sources
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Configure the config header
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/auspicious_library_config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/auspicious_library_config.hpp"
)

# Create library
add_library(auspicious_library
    ${LIB_SOURCES}
    "${CMAKE_CURRENT_BINARY_DIR}/include/auspicious_library_config.hpp"
)

# Specify library properties
target_compile_features(auspicious_library PUBLIC cxx_std_23)
target_include_directories(auspicious_library
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_compile_options(auspicious_library PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -g>
    $<$<CONFIG:Release>:-Wall -Wextra -Wpedantic -O3>
)

# Ensure position-independent code for shared libraries
set_target_properties(auspicious_library PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Enable testing if BUILD_TESTS is ON
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Add examples if BUILD_EXAMPLES is ON
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation rules
install(TARGETS auspicious_library
    EXPORT auspicious_library_targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT auspicious_library_targets
    FILE auspicious_library_targets.cmake
    NAMESPACE auspicious_library::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/auspicious_library
)

# Create a ConfigVersion file for find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/auspicious_library_config_version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Configure the Config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/auspicious_library_config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/auspicious_library_config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/auspicious_library
)

# Install the package config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/auspicious_library_config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/auspicious_library_config_version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/auspicious_library
)

# Export the package for use in the build tree
export(EXPORT auspicious_library_targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/auspicious_library_targets.cmake"
    NAMESPACE auspicious_library::
)
