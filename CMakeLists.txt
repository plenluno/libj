cmake_minimum_required(VERSION 2.8)

project(libj)

option(LIBJ_USE_BDW_GC "Use BDW-GC" OFF)
option(LIBJ_USE_GTEST "Use Google Test" OFF)
option(LIBJ_USE_EXCEPTION "Use Exception" OFF)

message(STATUS "LIBJ_USE_BDW_GC=${LIBJ_USE_BDW_GC}")
message(STATUS "LIBJ_USE_GTEST=${LIBJ_USE_GTEST}")
message(STATUS "LIBJ_USE_EXCEPTION=${LIBJ_USE_EXCEPTION}")

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h )

if(LIBJ_USE_BDW_GC)
    find_library(GC gc REQUIRED)
    if(NOT EXISTS ${GC})
        message(FATAL_ERROR "libgc not found.")
    endif()
endif(LIBJ_USE_BDW_GC)

if(LIBJ_USE_GTEST)
    find_library(GTEST gtest REQUIRED)
    if(NOT EXISTS ${GTEST})
        message(FATAL_ERROR "libgtest not found.")
    endif()
    find_library(PTHREAD pthread REQUIRED)
    if(NOT EXISTS ${PTHREAD})
        message(FATAL_ERROR "libpthread not found.")
    endif()
endif(LIBJ_USE_GTEST)

include_directories(
    include
    deps
    deps/boost-svn
    deps/jsoncpp/include
)

link_directories(
    ${CMAKE_BINARY_DIR}
)

set(libj-src-common
    src/array_list.cpp
    src/console.cpp
    src/error.cpp
    src/json.cpp
    src/js_array_buffer.cpp
    src/js_object.cpp
    src/linked_list.cpp
    src/map.cpp
    src/set.cpp
    src/status.cpp
    src/string.cpp
    src/string_buffer.cpp
    src/string_impl.cpp
)

if(LIBJ_USE_EXCEPTION)
set(libj-src
    src/exception.cpp
    ${libj-src-common}
)
else(LIBJ_USE_EXCEPTION)
set(libj-src
    src/no_exceptions.cpp
    ${libj-src-common}
)
endif(LIBJ_USE_EXCEPTION)

set(libj-deps-common
    cvtutf
    jsoncpp
)

if(LIBJ_USE_BDW_GC)
set(libj-deps
    gc
    ${libj-deps-common}
)
else(LIBJ_USE_BDW_GC)
set(libj-deps
    ${libj-deps-common}
)
endif(LIBJ_USE_BDW_GC)


# cvtutf
add_library(cvtutf STATIC
    deps/cvtutf/ConvertUTF.cpp
)

# jsoncpp
add_library(jsoncpp STATIC
    deps/jsoncpp/src/lib_json/json_reader.cpp
    deps/jsoncpp/src/lib_json/json_value.cpp
    deps/jsoncpp/src/lib_json/json_writer.cpp
)

# libj
add_library(j STATIC
    ${libj-src}
)
target_link_libraries(j
    ${libj-deps}
)
if(LIBJ_USE_EXCEPTION)
    set_target_properties(j
        PROPERTIES COMPILE_FLAGS "-Wall -fno-rtti")
else(LIBJ_USE_EXCEPTION)
    set_target_properties(j
        PROPERTIES COMPILE_FLAGS "-Wall -fno-rtti -fno-exceptions")
endif(LIBJ_USE_EXCEPTION)

# gtest
if(LIBJ_USE_GTEST)
    add_executable(libj-gtest
        gtest/gtest_array_list.cpp
        gtest/gtest_function.cpp
        gtest/gtest_immutable.cpp
        gtest/gtest_json.cpp
        gtest/gtest_jsoncpp.cpp
        gtest/gtest_js_array_buffer.cpp
        gtest/gtest_js_function.cpp
        gtest/gtest_js_object.cpp
        gtest/gtest_js_typed_array.cpp
        gtest/gtest_linked_list.cpp
        gtest/gtest_main.cpp
        gtest/gtest_map.cpp
        gtest/gtest_mutable.cpp
        gtest/gtest_null.cpp
        gtest/gtest_set.cpp
        gtest/gtest_singleton.cpp
        gtest/gtest_string.cpp
        gtest/gtest_string_buffer.cpp
        gtest/gtest_typed_array_list.cpp
        gtest/gtest_value.cpp
    )
    target_link_libraries(libj-gtest
        gtest
        j
        pthread
    )
    set_target_properties(libj-gtest
        PROPERTIES COMPILE_FLAGS "-Wall -DLIBJ_GTEST_BUILD_ERRORS")
endif(LIBJ_USE_GTEST)
