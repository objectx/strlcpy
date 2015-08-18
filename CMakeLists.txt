
cmake_minimum_required (VERSION 3.1)

project (STRLCPY
    LANGUAGES C
    VERSION 1.0.0.0)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set (CMAKE_CXX_FLAGS_DEBUG "-g")
set (CMAKE_C_FLAGS_DEBUG   "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O3")
set (CMAKE_C_FLAGS_RELEASE   "-O3")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions ("-DNDEBUG")
endif ()

set (COTIRE_VERBOSE TRUE)

include (CheckFunctionExists)
include (cotire OPTIONAL)

enable_testing ()

check_function_exists (strnlen  HAVE_STRNLEN)
check_function_exists (strlen_s HAVE_STRLEN_S)
check_function_exists (strlcpy  HAVE_STRLCPY)
check_function_exists (strlcat  HAVE_STRLCAT)

configure_file ("${CMAKE_SOURCE_DIR}/config.h.in" "${CMAKE_BINARY_DIR}/config.h" @ONLY)
add_definitions ("-DHAVE_CONFIG_H=1")

add_subdirectory (strlcpy)
add_subdirectory (test_strlcpy)