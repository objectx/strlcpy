
cmake_minimum_required (VERSION 3.1)

enable_language (CXX)

set (TARGET test-strlcpy)
set (SOURCE_FILES main.cpp strlcpy.cpp strlcat.cpp strconcat.cpp)

add_executable (${TARGET} ${SOURCE_FILES})
target_include_directories (${TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/Catch/include" ${CMAKE_BINARY_DIR})
target_link_libraries (${TARGET} strlcpy)
set_target_properties (${TARGET} PROPERTIES
    COTIRE_PREFIX_HEADER_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/Catch/include/internal;${CMAKE_SOURCE_DIR}/Catch/include/reporters")
set_source_files_properties (main.cpp PROPERTIES COTIRE_EXCLUDED TRUE)

if (COMMAND cotire)
    cotire (${TARGET})
endif ()

add_test (NAME test-strlcpy
    COMMAND test-strlcpy)
