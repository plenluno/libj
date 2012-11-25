cmake_minimum_required(VERSION 2.8)

project(libj)

# options ------------------------------------------------------------------------------------------

option(LIBJ_BUILD_GTEST "Build Google tests" OFF)
option(LIBJ_USE_CXX11 "Use C++11" OFF)
option(LIBJ_USE_BDW_GC "Use BDW-GC" OFF)
option(LIBJ_USE_EXCEPTION "Use exceptions" OFF)

message(STATUS "LIBJ_BUILD_GTEST=${LIBJ_BUILD_GTEST}")
message(STATUS "LIBJ_USE_CXX11=${LIBJ_USE_CXX11}")
message(STATUS "LIBJ_USE_BDW_GC=${LIBJ_USE_BDW_GC}")
message(STATUS "LIBJ_USE_EXCEPTION=${LIBJ_USE_EXCEPTION}")

# find libraries -----------------------------------------------------------------------------------

if(LIBJ_USE_BDW_GC)
    find_library(GC gc REQUIRED)
    if(NOT EXISTS ${GC})
        message(FATAL_ERROR "libgc not found.")
    endif()
endif(LIBJ_USE_BDW_GC)

if(LIBJ_BUILD_GTEST)
    find_library(GTEST gtest REQUIRED)
    if(NOT EXISTS ${GTEST})
        message(FATAL_ERROR "libgtest not found.")
    endif()
    find_library(PTHREAD pthread REQUIRED)
    if(NOT EXISTS ${PTHREAD})
        message(FATAL_ERROR "libpthread not found.")
    endif()
endif(LIBJ_BUILD_GTEST)

# configure ----------------------------------------------------------------------------------------

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h )

# set variables ------------------------------------------------------------------------------------

set(libj-include
    include
    deps
    deps/iv
    deps/jsoncpp/include
)

if(NOT LIBJ_USE_CXX11 OR LIBJ_BUILD_GTEST)
    set(libj-include
        ${libj-include}
        deps/boost-svn
    )
endif(NOT LIBJ_USE_CXX11 OR LIBJ_BUILD_GTEST)

set(libj-src
    src/array_list.cpp
    src/console.cpp
    src/constant.cpp
    src/endian.cpp
    src/error.cpp
    src/json.cpp
    src/js_array.cpp
    src/js_array_buffer.cpp
    src/js_object.cpp
    src/js_regexp.cpp
    src/linked_list.cpp
    src/map.cpp
    src/set.cpp
    src/status.cpp
    src/string.cpp
    src/string_buffer.cpp
)

if(LIBJ_USE_EXCEPTION)
    set(libj-src
        src/exception.cpp
        ${libj-src}
    )
else(LIBJ_USE_EXCEPTION)
    set(libj-src
        src/no_exception.cpp
        ${libj-src}
    )
endif(LIBJ_USE_EXCEPTION)

set(libj-deps
    cvtutf
    jsoncpp
    regexp
    v8dtoa
)

if(APPLE)
    set(libj-deps
        iconv
        ${libj-deps}
    )
endif(APPLE)

if(LIBJ_USE_BDW_GC)
    set(libj-deps
        gc
        ${libj-deps}
    )
endif(LIBJ_USE_BDW_GC)

set(libj-cflags
    -Wall
    -fno-rtti
)

if(LIBJ_USE_CXX11)
    set(libj-cflags
        ${libj-cflags}
        --std=c++0x
    )
endif(LIBJ_USE_CXX11)

if(NOT LIBJ_USE_EXCEPTION)
    set(libj-cflags
        ${libj-cflags}
        -fno-exceptions
    )
endif(NOT LIBJ_USE_EXCEPTION)

string(REPLACE ";" " " libj-cflags "${libj-cflags}")

# build libraries ----------------------------------------------------------------------------------

include_directories(
    ${libj-include}
)

link_directories(
    ${CMAKE_BINARY_DIR}
)

## cvtutf
add_library(cvtutf STATIC
    src/glue/cvtutf.cpp
)

set_target_properties(cvtutf PROPERTIES
    COMPILE_FLAGS ${libj-cflags}
)

## jsoncpp
add_library(jsoncpp STATIC
    deps/jsoncpp/src/lib_json/json_reader.cpp
    deps/jsoncpp/src/lib_json/json_value.cpp
    deps/jsoncpp/src/lib_json/json_writer.cpp
)

## regexp
add_library(regexp STATIC
    src/glue/regexp.cpp
)

if(NOT APPLE OR LIBJ_USE_CXX11)
set_target_properties(regexp PROPERTIES
    COMPILE_FLAGS "--std=c++0x")
endif(NOT APPLE OR LIBJ_USE_CXX11)

## v8dtoa
add_library(v8dtoa STATIC
    deps/iv/iv/lv5/third_party/netlib_dtoa/netlib_dtoa.c
    deps/iv/iv/lv5/third_party/v8_dtoa/checks.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/conversions.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/diy-fp.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/fast-dtoa.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/platform.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/utils.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/v8-dtoa.cc
)

## libj
add_library(j STATIC
    ${libj-src}
)

target_link_libraries(j
    ${libj-deps}
)

set_target_properties(j PROPERTIES
    COMPILE_FLAGS "${libj-cflags}"
)

# build gtests -------------------------------------------------------------------------------------

if(LIBJ_BUILD_GTEST)
    add_executable(libj-gtest
        gtest/gtest_array_list.cpp
        gtest/gtest_console.cpp
        gtest/gtest_cvtutf.cpp
        gtest/gtest_error.cpp
        gtest/gtest_function.cpp
        gtest/gtest_immutable.cpp
        gtest/gtest_json.cpp
        gtest/gtest_jsoncpp.cpp
        gtest/gtest_js_array.cpp
        gtest/gtest_js_array_buffer.cpp
        gtest/gtest_js_function.cpp
        gtest/gtest_js_object.cpp
        gtest/gtest_js_regexp.cpp
        gtest/gtest_linked_list.cpp
        gtest/gtest_main.cpp
        gtest/gtest_map.cpp
        gtest/gtest_mutable.cpp
        gtest/gtest_set.cpp
        gtest/gtest_singleton.cpp
        gtest/gtest_status.cpp
        gtest/gtest_string.cpp
        gtest/gtest_string_buffer.cpp
        gtest/gtest_typed_array_list.cpp
        gtest/gtest_typed_js_array.cpp
        gtest/gtest_typed_linked_list.cpp
        gtest/gtest_typed_value_holder.cpp
        gtest/gtest_value.cpp
        gtest/gtest_value_holder.cpp
    )
    target_link_libraries(libj-gtest
        gtest
        j
        pthread
    )
    if(LIBJ_USE_CXX11)
        set_target_properties(libj-gtest PROPERTIES
            COMPILE_FLAGS "-Wall --std=c++0x -fpermissive"
        )
    else(LIBJ_USE_CXX11)
        set_target_properties(libj-gtest PROPERTIES
            COMPILE_FLAGS "-Wall"
        )
    endif(LIBJ_USE_CXX11)
endif(LIBJ_BUILD_GTEST)
