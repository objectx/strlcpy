
cmake_minimum_required (VERSION 3.1)

set (TARGET strlcpy)

set (SOURCE_FILES strlcpy.c strlcat.c strconcat.c)

include_directories ("${CMAKE_BINARY_DIR}")

add_library (${TARGET} STATIC ${SOURCE_FILES})
