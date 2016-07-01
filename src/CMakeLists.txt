
cmake_minimum_required (VERSION 3.5)

set (TARGET strlcpy)

set (SOURCE_FILES strlcpy.c strlcat.c)

include_directories ("${CMAKE_BINARY_DIR}")

add_library (${TARGET} STATIC ${SOURCE_FILES})
    # target_include_directories (${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include)
    #target_compile_features (${TARGET} PUBLIC cxx_auto_type)

add_library (strconcat INTERFACE)
    target_include_directories (strconcat INTERFACE ${STRLCPY_SOURCE_DIR}/include)
    target_compile_features (strconcat INTERFACE cxx_auto_type cxx_variadic_templates)
