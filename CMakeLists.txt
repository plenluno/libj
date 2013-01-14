# Copyright (c) 2012-2013 Plenluno All rights reserved.

cmake_minimum_required(VERSION 2.8)

project(libj)

include(CMakeDependentOption)

# options ------------------------------------------------------------------------------------------

option(LIBJ_USE_BDWGC "Use BDW-GC" OFF)
option(LIBJ_USE_CXX11 "Use C++11" OFF)
option(LIBJ_USE_EXCEPTION "Use Exceptions" OFF)
option(LIBJ_USE_JSCRE "Use JSCRE" OFF)
option(LIBJ_USE_JSONCPP "Use JsonCpp" OFF)
option(LIBJ_USE_THREAD "Use Threads" ON)
option(LIBJ_BUILD_GTEST "Build Google Test" OFF)
option(LIBJ_BUILD_TEST "Build Tests" OFF)
option(LIBJ_DEPRECATED "Deprecated" OFF)

cmake_dependent_option(LIBJ_BUILD_BDWGC "Build BDW-GC" ON "LIBJ_USE_BDWGC" OFF)

message(STATUS "LIBJ_USE_BDWGC=${LIBJ_USE_BDWGC}")
message(STATUS "LIBJ_USE_CXX11=${LIBJ_USE_CXX11}")
message(STATUS "LIBJ_USE_EXCEPTION=${LIBJ_USE_EXCEPTION}")
message(STATUS "LIBJ_USE_JSCRE=${LIBJ_USE_JSCRE}")
message(STATUS "LIBJ_USE_JSONCPP=${LIBJ_USE_JSONCPP}")
message(STATUS "LIBJ_USE_THREAD=${LIBJ_USE_THREAD}")
message(STATUS "LIBJ_BUILD_BDWGC=${LIBJ_BUILD_BDWGC}")
message(STATUS "LIBJ_BUILD_GTEST=${LIBJ_BUILD_GTEST}")
message(STATUS "LIBJ_BUILD_TEST=${LIBJ_BUILD_TEST}")

# variables ----------------------------------------------------------------------------------------

## libj-include
set(libj-include
    include
    deps
    deps/iv
)

if(LIBJ_USE_JSCRE)
    set(libj-include
        ${libj-include}
        deps/jscre
    )
endif(LIBJ_USE_JSCRE)

if(LIBJ_USE_JSONCPP)
    set(libj-include
        ${libj-include}
        deps/jsoncpp/include
    )
else(LIBJ_USE_JSONCPP)
    set(libj-include
        ${libj-include}
        deps/picojson
    )
endif(LIBJ_USE_JSONCPP)

if(LIBJ_BUILD_GTEST)
    set(libj-includd
        deps/googletest/include
    )
endif(LIBJ_BUILD_GTEST)

if(NOT LIBJ_USE_CXX11 OR LIBJ_BUILD_TEST)
    set(libj-include
        ${libj-include}
        deps/boost-svn
    )
endif(NOT LIBJ_USE_CXX11 OR LIBJ_BUILD_TEST)

## libj-src
set(libj-src
    src/array_list.cpp
    src/console.cpp
    src/constant.cpp
    src/endian.cpp
    src/error.cpp
    src/json.cpp
    src/js_array.cpp
    src/js_array_buffer.cpp
    src/js_data_view.cpp
    src/js_object.cpp
    src/js_regexp.cpp
    src/linked_list.cpp
    src/map.cpp
    src/set.cpp
    src/status.cpp
    src/string.cpp
    src/string_buffer.cpp
    src/symbol.cpp
    src/value_holder.cpp
)

if(LIBJ_USE_CXX11)
    set(libj-src
        ${libj-src}
        src/js_closure.cpp
    )
endif(LIBJ_USE_CXX11)

if(LIBJ_USE_THREAD)
    set(libj-src
        ${libj-src}
        src/blocking_linked_queue.cpp
        src/concurrent_linked_queue.cpp
        src/executors.cpp
        src/thread.cpp
    )
endif(LIBJ_USE_THREAD)

if(LIBJ_USE_EXCEPTION)
    set(libj-src
        ${libj-src}
        src/exception.cpp
    )
else(LIBJ_USE_EXCEPTION)
    set(libj-src
        ${libj-src}
        src/no_exception.cpp
    )
endif(LIBJ_USE_EXCEPTION)

## libj-json-src
set(libj-json-src
    src/glue/json.cpp
)

if(LIBJ_USE_JSONCPP)
    set(libj-json-src
        ${libj-json-src}
        deps/jsoncpp/src/lib_json/json_reader.cpp
        deps/jsoncpp/src/lib_json/json_value.cpp
        deps/jsoncpp/src/lib_json/json_writer.cpp
    )
endif(LIBJ_USE_JSONCPP)

## libj-test-src
set(libj-test-src
    gtest/gtest_array_list.cpp
    gtest/gtest_console.cpp
    gtest/gtest_cvtutf.cpp
    gtest/gtest_error.cpp
    gtest/gtest_function.cpp
    gtest/gtest_immutable.cpp
    gtest/gtest_json.cpp
    gtest/gtest_js_array.cpp
    gtest/gtest_js_array_buffer.cpp
    gtest/gtest_js_data_view.cpp
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

if(LIBJ_USE_CXX11)
    set(libj-test-src
        ${libj-test-src}
        gtest/gtest_js_closure.cpp
    )
endif(LIBJ_USE_CXX11)

if(LIBJ_USE_THREAD)
    set(libj-test-src
        ${libj-test-src}
        gtest/gtest_blocking_linked_queue.cpp
        gtest/gtest_concurrent_linked_queue.cpp
        gtest/gtest_executor_service.cpp
        gtest/gtest_thread.cpp
    )
endif(LIBJ_USE_THREAD)

## libj-deps
set(libj-deps
    cvtutf
    dtoa
    json
    ndtoa
    pthread
    regexp
)

if(APPLE)
    set(libj-deps
        ${libj-deps}
        iconv
    )
endif(APPLE)

if(LIBJ_USE_BDWGC)
    set(libj-deps
        ${libj-deps}
        gc
    )
endif(LIBJ_USE_BDWGC)

if(LIBJ_USE_JSCRE)
    set(libj-deps
        ${libj-deps}
        jscre
    )
endif(LIBJ_USE_JSCRE)

## libj-cflags
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

## libj-deps-cflags
set(libj-deps-cflags
    -fno-rtti
)

if(LIBJ_USE_CXX11)
    set(libj-deps-cflags
        ${libj-deps-cflags}
        --std=c++0x
    )
endif(LIBJ_USE_CXX11)

string(REPLACE ";" " " libj-deps-cflags "${libj-deps-cflags}")

## libj-test-cflags
set(libj-test-cflags
    -Wall
)

if(NOT APPLE)
    set(libj-test-cflags
        ${libj-test-cflags}
        -fpermissive
    )
endif(NOT APPLE)

if(LIBJ_USE_CXX11)
    set(libj-test-cflags
        ${libj-test-cflags}
        --std=c++0x
    )
endif(LIBJ_USE_CXX11)

string(REPLACE ";" " " libj-test-cflags "${libj-test-cflags}")

# configure ----------------------------------------------------------------------------------------

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h )

# find libraries -----------------------------------------------------------------------------------

find_library(PTHREAD pthread REQUIRED)
if(NOT EXISTS ${PTHREAD})
    message(FATAL_ERROR "libpthread not found.")
endif()

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
    COMPILE_FLAGS ${libj-deps-cflags}
)

## json
add_library(json STATIC
    ${libj-json-src}
)

set_target_properties(json PROPERTIES
    COMPILE_FLAGS ${libj-deps-cflags}
)

## jscre
if(LIBJ_USE_JSCRE)
    add_subdirectory(deps/jscre)
endif(LIBJ_USE_JSCRE)

## regexp
add_library(regexp STATIC
    src/glue/regexp.cpp
)

if(NOT APPLE OR LIBJ_USE_CXX11)
    set_target_properties(regexp PROPERTIES
        COMPILE_FLAGS "--std=c++0x"
    )
endif(NOT APPLE OR LIBJ_USE_CXX11)

## dtoa
add_library(dtoa STATIC
    src/glue/dtoa.cpp
    deps/iv/iv/lv5/third_party/v8_dtoa/checks.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/conversions.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/diy-fp.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/fast-dtoa.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/platform.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/utils.cc
    deps/iv/iv/lv5/third_party/v8_dtoa/v8-dtoa.cc
)

set_target_properties(dtoa PROPERTIES
    COMPILE_FLAGS ${libj-deps-cflags}
)

add_library(ndtoa STATIC
    deps/iv/iv/lv5/third_party/netlib_dtoa/netlib_dtoa.c
)

## bdw-gc
if(LIBJ_BUILD_BDWGC)
    add_custom_command(
        TARGET json PRE_BUILD
        COMMAND rsync -av ${CMAKE_CURRENT_LIST_DIR}/deps/bdwgc ${CMAKE_BINARY_DIR}/deps/
        COMMAND rsync -av ${CMAKE_CURRENT_LIST_DIR}/deps/libatomic_ops ${CMAKE_BINARY_DIR}/deps/bdwgc/
        COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && ./autogen.sh
        COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && ./configure
        COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && make
        COMMAND ln -sf ${CMAKE_BINARY_DIR}/deps/bdwgc/.libs/libgc.a ${CMAKE_BINARY_DIR}/libgc.a
    )
endif(LIBJ_BUILD_BDWGC)

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

# build tests --------------------------------------------------------------------------------------

if(LIBJ_BUILD_GTEST)
    add_subdirectory(
        deps/googletest
    )
endif(LIBJ_BUILD_GTEST)

if(LIBJ_BUILD_TEST)
    add_executable(libj-test
        ${libj-test-src}
    )

    target_link_libraries(libj-test
        gtest
        j
        pthread
    )

    set_target_properties(libj-test PROPERTIES
        COMPILE_FLAGS "${libj-test-cflags}"
    )
endif(LIBJ_BUILD_TEST)
