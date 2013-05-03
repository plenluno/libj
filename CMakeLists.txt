# Copyright (c) 2012-2013 Plenluno All rights reserved.

cmake_minimum_required(VERSION 2.8)

project(libj)

include(CMakeDependentOption)

# options ----------------------------------------------------------------------

option(LIBJ_DEBUG         "Debug Mode"        OFF)
option(LIBJ_USE_BDWGC     "Use BDW-GC"        OFF)
option(LIBJ_USE_CXX11     "Use C++11"         OFF)
option(LIBJ_USE_EXCEPTION "Use Exceptions"    OFF)
option(LIBJ_USE_ICONV     "Use iconv"         OFF)
option(LIBJ_USE_JSCRE     "Use JSCRE"         OFF)
option(LIBJ_USE_JSONCPP   "Use JsonCpp"       OFF)
option(LIBJ_USE_THREAD    "Use Threads"       OFF)
option(LIBJ_USE_UTF32     "Use UTF32"         OFF)
option(LIBJ_BUILD_GTEST   "Build Google Test" OFF)
option(LIBJ_BUILD_TEST    "Build Unit Tests"  OFF)

cmake_dependent_option(LIBJ_BUILD_BDWGC
    "Build BDW-GC" ON
    "LIBJ_USE_BDWGC" OFF
)

## check
if(LIBJ_USE_BDWGC AND NOT LIBJ_BUILD_BDWGC)
    message(FATAL_ERROR "LIBJ_USE_BDWGC=ON and LIBJ_BUILD_BDWGC=OFF")
endif(LIBJ_USE_BDWGC AND NOT LIBJ_BUILD_BDWGC)

if(LIBJ_USE_BDWGC AND LIBJ_USE_THREAD)
    message(FATAL_ERROR "LIBJ_USE_BDWGC=ON and LIBJ_USE_THREAD=ON")
endif(LIBJ_USE_BDWGC AND LIBJ_USE_THREAD)

## status
message(STATUS "LIBJ_DEBUG=${LIBJ_DEBUG}")
message(STATUS "LIBJ_USE_BDWGC=${LIBJ_USE_BDWGC}")
message(STATUS "LIBJ_USE_CXX11=${LIBJ_USE_CXX11}")
message(STATUS "LIBJ_USE_EXCEPTION=${LIBJ_USE_EXCEPTION}")
message(STATUS "LIBJ_USE_ICONV=${LIBJ_USE_ICONV}")
message(STATUS "LIBJ_USE_JSCRE=${LIBJ_USE_JSCRE}")
message(STATUS "LIBJ_USE_JSONCPP=${LIBJ_USE_JSONCPP}")
message(STATUS "LIBJ_USE_THREAD=${LIBJ_USE_THREAD}")
message(STATUS "LIBJ_USE_UTF32=${LIBJ_USE_UTF32}")
message(STATUS "LIBJ_BUILD_BDWGC=${LIBJ_BUILD_BDWGC}")
message(STATUS "LIBJ_BUILD_GTEST=${LIBJ_BUILD_GTEST}")
message(STATUS "LIBJ_BUILD_TEST=${LIBJ_BUILD_TEST}")

# variables --------------------------------------------------------------------

## libj-include
set(libj-include
    include
    deps/iv
    deps/boost-svn
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

if(NOT LIBJ_USE_ICONV)
    set(libj-include
        ${libj-include}
        deps/convertutf
    )
endif(NOT LIBJ_USE_ICONV)

if(LIBJ_BUILD_BDWGC)
    set(libj-include
        ${libj-include}
        deps/bdwgc/include
    )
endif(LIBJ_BUILD_BDWGC)

if(LIBJ_BUILD_GTEST)
    set(libj-include
        ${libj-include}
        deps/googletest
        deps/googletest/include
    )
endif(LIBJ_BUILD_GTEST)

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
    src/js_date.cpp
    src/js_object.cpp
    src/js_regexp.cpp
    src/linked_list.cpp
    src/map.cpp
    src/math.cpp
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
        src/atomic_integer.cpp
        src/atomic_long.cpp
        src/blocking_linked_queue.cpp
        src/concurrent_linked_queue.cpp
        src/concurrent_map.cpp
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
    gtest/gtest_js_date.cpp
    gtest/gtest_js_function.cpp
    gtest/gtest_js_object.cpp
    gtest/gtest_js_regexp.cpp
    gtest/gtest_linked_list.cpp
    gtest/gtest_main.cpp
    gtest/gtest_map.cpp
    gtest/gtest_math.cpp
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
        gtest/gtest_atomic_integer.cpp
        gtest/gtest_atomic_long.cpp
        gtest/gtest_blocking_linked_queue.cpp
        gtest/gtest_concurrent_linked_queue.cpp
        gtest/gtest_concurrent_map.cpp
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
    regexp
)

if(LIBJ_USE_ICONV)
    if(APPLE)
        set(libj-deps
            ${libj-deps}
            iconv
        )
    endif(APPLE)
else(LIBJ_USE_ICONV)
    set(libj-deps
        ${libj-deps}
        convertutf
    )
endif(LIBJ_USE_ICONV)

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

if(UNIX)
    if(NOT ANDROID)
        set(libj-deps
            ${libj-deps}
            pthread
        )
    endif(NOT ANDROID)

    if(LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)
        set(libj-deps
            ${libj-deps}
            trace
        )
    endif(LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)
endif(UNIX)

## libj-test-deps
set(libj-test-deps
    gtest
    j
)

if(UNIX AND NOT ANDROID)
    set(libj-test-deps
        ${libj-test-deps}
        pthread
    )
endif(UNIX AND NOT ANDROID)

## libj-cflags
if(UNIX)
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

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(libj-cflags
            ${libj-cflags}
            -Wno-unused-variable
            -Wno-unused-parameter
        )
    endif(CMAKE_BUILD_TYPE STREQUAL "Release")

    if(LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)
        set(libj-cflags
            ${libj-cflags}
            -finstrument-functions   
        )
    endif(LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)
else(UNIX)
    set(libj-cflags
        /W4
    )
endif(UNIX)

string(REPLACE ";" " " libj-cflags "${libj-cflags}")

## libj-deps-cflags
if(UNIX)
    set(libj-deps-cflags
        -fno-rtti
    )

    if(LIBJ_USE_CXX11)
        set(libj-deps-cflags
            ${libj-deps-cflags}
            --std=c++0x
        )
    endif(LIBJ_USE_CXX11)
else(UNIX)
    set(libj-deps-cflags
        /W1
    )
endif(UNIX)

string(REPLACE ";" " " libj-deps-cflags "${libj-deps-cflags}")

## libj-test-cflags
if(UNIX)
    set(libj-test-cflags
        -Wall
        -Wno-sign-compare
        -Wno-unused-value
    )

    if(NOT APPLE)
        set(libj-test-cflags
            ${libj-test-cflags}
            -fpermissive
            -Wno-pragmas
        )
    endif(NOT APPLE)

    if(LIBJ_USE_CXX11)
        set(libj-test-cflags
            ${libj-test-cflags}
            --std=c++0x
        )
    endif(LIBJ_USE_CXX11)

    if(LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)
        set(libj-test-cflags
            ${libj-test-cflags}
            -finstrument-functions   
        )
    endif(LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)
else(UNIX)
    set(libj-test-cflags
        /D_VARIADIC_MAX=10
    )
endif(UNIX)

string(REPLACE ";" " " libj-test-cflags "${libj-test-cflags}")

# configure --------------------------------------------------------------------

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/libj/config.h )

# build libraries --------------------------------------------------------------

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

if(NOT LIBJ_USE_ICONV)
    add_library(convertutf STATIC
        deps/convertutf/ConvertUTF.cpp
    )

    if(UNIX AND LIBJ_USE_CXX11)
        set_target_properties(convertutf PROPERTIES
            COMPILE_FLAGS "--std=c++0x"
        )
    endif(UNIX AND LIBJ_USE_CXX11)
endif(NOT LIBJ_USE_ICONV)

## json
add_library(json STATIC
    ${libj-json-src}
)

set_target_properties(json PROPERTIES
    COMPILE_FLAGS ${libj-deps-cflags}
)

## jscre
if(LIBJ_USE_JSCRE)
    add_subdirectory(
        deps/jscre
    )
endif(LIBJ_USE_JSCRE)

## regexp
add_library(regexp STATIC
    src/glue/regexp.cpp
)

if(UNIX AND NOT LIBJ_USE_JSCRE AND (NOT APPLE OR LIBJ_USE_CXX11))
    set_target_properties(regexp PROPERTIES
        COMPILE_FLAGS "--std=c++0x"
    )
endif(UNIX AND NOT LIBJ_USE_JSCRE AND (NOT APPLE OR LIBJ_USE_CXX11))

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
    if(LIBJ_USE_THREAD)
        add_custom_command(
            TARGET json PRE_BUILD
            COMMAND rsync -av
                ${CMAKE_CURRENT_LIST_DIR}/deps/bdwgc
                ${CMAKE_BINARY_DIR}/deps/
            COMMAND rsync -av
                ${CMAKE_CURRENT_LIST_DIR}/deps/libatomic_ops
                ${CMAKE_BINARY_DIR}/deps/bdwgc/
            COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && ./autogen.sh
            COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && ./configure
            COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && make
            COMMAND ln -sf
                ${CMAKE_BINARY_DIR}/deps/bdwgc/.libs/libgc.a
                ${CMAKE_BINARY_DIR}/libgc.a
        )
    else(LIBJ_USE_THREAD)
        add_subdirectory(
            deps/bdwgc
        )
    endif(LIBJ_USE_THREAD)
endif(LIBJ_BUILD_BDWGC)

## trace
if(UNIX AND LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)
    add_library(trace STATIC
        src/trace.cpp
    )

    target_link_libraries(trace
        dl
        regexp
    )

    set_target_properties(trace PROPERTIES
        COMPILE_FLAGS ${libj-deps-cflags}
    )
endif(UNIX AND LIBJ_DEBUG AND NOT LIBJ_USE_THREAD)

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

# build tests ------------------------------------------------------------------

if(LIBJ_BUILD_GTEST)
    if(UNIX)
        add_subdirectory(
            deps/googletest
        )
    else(UNIX)
        add_library(gtest STATIC
            deps/googletest/src/gtest-all.cc
        )

        set_target_properties(gtest PROPERTIES
            COMPILE_FLAGS "/D_VARIADIC_MAX=10"
        )
    endif(UNIX)
endif(LIBJ_BUILD_GTEST)

if(LIBJ_BUILD_TEST)
    add_executable(libj-test
        ${libj-test-src}
    )

    target_link_libraries(libj-test
        ${libj-test-deps}
    )

    set_target_properties(libj-test PROPERTIES
        COMPILE_FLAGS "${libj-test-cflags}"
    )
endif(LIBJ_BUILD_TEST)
