
cmake_minimum_required (VERSION 3.1)

enable_language (CXX)

set (TARGET test-strlcpy)
set (SOURCE_FILES main.cpp strlcpy.cpp strlcat.cpp strconcat.cpp)

message ("CATCH: ${CATCH_INCLUDE_DIR}")
include_directories ("${CATCH_INCLUDE_DIR}" ${CMAKE_BINARY_DIR})

add_executable (${TARGET} ${SOURCE_FILES})
    target_link_libraries (${TARGET} PRIVATE strlcpy strconcat)
    set_target_properties (${TARGET} PROPERTIES
         COTIRE_PREFIX_HEADER_INCLUDE_PATH "${CATCH_INCLUDE_DIR}")
    set_source_files_properties (main.cpp PROPERTIES COTIRE_EXCLUDED TRUE)

if (COMMAND cotire)
    # cotire (${TARGET})
endif ()

add_test (NAME test-strlcpy
    COMMAND test-strlcpy)
