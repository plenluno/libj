# Copyright (c) 2012-2013 Plenluno All rights reserved.

cmake_minimum_required(VERSION 2.8)

project(libj)

include(CMakeDependentOption)

# options ----------------------------------------------------------------------

if(NOT SUBMODULE_LIBJ)
    option(LIBJ_DEBUG         "Debug Mode"        OFF)
    option(LIBJ_TRACE         "Trace Mode"        OFF)
    option(LIBJ_USE_BDWGC     "Use BDW-GC"        OFF)
    option(LIBJ_USE_CXX11     "Use C++11"         OFF)
    option(LIBJ_USE_EXCEPTION "Use Exceptions"    OFF)
    option(LIBJ_USE_ICONV     "Use iconv"         OFF)
    option(LIBJ_USE_THREAD    "Use Threads"       OFF)
    option(LIBJ_USE_UTF32     "Use UTF32"         OFF)
    option(LIBJ_USE_XML       "Use XML"           ON)
    option(LIBJ_BUILD_TEST    "Build Unit Tests"  OFF)

    cmake_dependent_option(LIBJ_BUILD_GTEST
        "Build Google Test" ON
        "LIBJ_BUILD_TEST" OFF
    )
endif(NOT SUBMODULE_LIBJ)

## check
if(LIBJ_TRACE AND NOT LIBJ_DEBUG)
    message(FATAL_ERROR "LIBJ_TRACE=ON but LIBJ_DEBUG=OFF")
endif(LIBJ_TRACE AND NOT LIBJ_DEBUG)

if(LIBJ_TRACE AND LIBJ_USE_THREAD)
    message(FATAL_ERROR "LIBJ_TRACE=ON but LIBJ_USE_THREAD=ON")
endif(LIBJ_TRACE AND LIBJ_USE_THREAD)

if(LIBJ_USE_BDWGC AND LIBJ_USE_THREAD)
    message(FATAL_ERROR "LIBJ_USE_BDWGC=ON but LIBJ_USE_THREAD=ON")
endif(LIBJ_USE_BDWGC AND LIBJ_USE_THREAD)

if(MSVC AND LIBJ_USE_UTF32)
    message(FATAL_ERROR "LIBJ_USE_UTF32 not supported in Windows")
endif(MSVC AND LIBJ_USE_UTF32)

## status
message(STATUS "LIBJ_DEBUG=${LIBJ_DEBUG}")
message(STATUS "LIBJ_TRACE=${LIBJ_TRACE}")
message(STATUS "LIBJ_USE_BDWGC=${LIBJ_USE_BDWGC}")
message(STATUS "LIBJ_USE_CXX11=${LIBJ_USE_CXX11}")
message(STATUS "LIBJ_USE_EXCEPTION=${LIBJ_USE_EXCEPTION}")
message(STATUS "LIBJ_USE_ICONV=${LIBJ_USE_ICONV}")
message(STATUS "LIBJ_USE_THREAD=${LIBJ_USE_THREAD}")
message(STATUS "LIBJ_USE_UTF32=${LIBJ_USE_UTF32}")
message(STATUS "LIBJ_BUILD_TEST=${LIBJ_BUILD_TEST}")

# variables --------------------------------------------------------------------

## libj-include
set(libj-include
    include
    deps/iv
    deps/jscre
    deps/picojson
    deps/boost-svn
)

if(LIBJ_USE_BDWGC)
    set(libj-include
        ${libj-include}
        deps/bdwgc/include
    )
endif(LIBJ_USE_BDWGC)

if(NOT LIBJ_USE_ICONV)
    set(libj-include
        ${libj-include}
        deps/convertutf
    )
endif(NOT LIBJ_USE_ICONV)

if(LIBJ_USE_XML)
    set(libj-include
        ${libj-include}
        deps/pugixml/src
    )
endif(LIBJ_USE_XML)

if(LIBJ_BUILD_TEST)
    set(libj-include
        ${libj-include}
        deps/googletest
        deps/googletest/include
    )
endif(LIBJ_BUILD_TEST)

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
    src/glue/cvtutf.cpp
    src/glue/dtoa.cpp
    src/glue/json.cpp
    src/glue/regexp.cpp
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

if(LIBJ_USE_XML)
    set(libj-src
        ${libj-src}
        src/xml/document.cpp
    )
endif(LIBJ_USE_XML)

## libj-deps
set(libj-deps
    jscre
    nldtoa
    v8dtoa
)

if(LIBJ_USE_BDWGC)
    set(libj-deps
        ${libj-deps}
        gc
    )
endif(LIBJ_USE_BDWGC)

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

if(UNIX)
    if(NOT ANDROID)
        set(libj-deps
            ${libj-deps}
            pthread
        )
    endif(NOT ANDROID)

    if(LIBJ_TRACE)
        set(libj-deps
            ${libj-deps}
            trace
        )
    endif(LIBJ_TRACE)
endif(UNIX)

## libj-linklibs
set(libj-linklibs
    j
)

if(LIBJ_BUILD_TEST)
    set(libj-linklibs
        ${libj-linklibs}
        gtest
    )
endif(LIBJ_BUILD_TEST)

if(LIBJ_USE_CXX11 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(libj-linklibs
        ${libj-linklibs}
        c++
        c++abi
    )
endif(LIBJ_USE_CXX11 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

## libj-cxx11-cflags
set(libj-cxx11-cflags
    --std=c++0x
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(libj-cxx11-cflags
        ${libj-cxx11-cflags}
        -stdlib=libc++
    )
endif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

## libj-common-cflags
set(libj-common-cflags
    -fno-rtti
)

if(LIBJ_USE_CXX11)
    set(libj-common-cflags
        ${libj-common-cflags}
        ${libj-cxx11-cflags}
    )
endif(LIBJ_USE_CXX11)

if(NOT LIBJ_USE_EXCEPTION)
    set(libj-common-cflags
        ${libj-common-cflags}
        -fno-exceptions
    )
endif(NOT LIBJ_USE_EXCEPTION)

if(NOT LIBJ_USE_UTF32)
    set(libj-common-cflags
        ${libj-common-cflags}
        -fshort-wchar
    )
endif(NOT LIBJ_USE_UTF32)

## libj-cflags
if(UNIX)
    set(libj-cflags
        -Wall
        ${libj-common-cflags}
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(libj-cflags
            ${libj-cflags}
            -Wno-unused-variable
            -Wno-unused-parameter
        )
    endif(CMAKE_BUILD_TYPE STREQUAL "Release")

    if(LIBJ_TRACE)
        set(libj-cflags
            ${libj-cflags}
            -finstrument-functions   
        )
    endif(LIBJ_TRACE)
else(UNIX)
    set(libj-cflags
        /W4
    )
endif(UNIX)

## libj-deps-cflags
if(UNIX)
    set(libj-deps-cflags
        ${libj-common-cflags}
    )
else(UNIX)
    set(libj-deps-cflags
        /W1
    )
endif(UNIX)

## libj-test-cflags
if(UNIX)
    set(libj-test-cflags
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
            ${libj-cxx11-cflags}
        )
    endif(LIBJ_USE_CXX11)

    if(LIBJ_TRACE)
        set(libj-test-cflags
            ${libj-test-cflags}
            -finstrument-functions   
        )
    endif(LIBJ_TRACE)
else(UNIX)
    set(libj-test-cflags
        /D_VARIADIC_MAX=10
    )
endif(UNIX)

string(REPLACE ";" " " libj-cflags       "${libj-cflags}")
string(REPLACE ";" " " libj-deps-cflags  "${libj-deps-cflags}")
string(REPLACE ";" " " libj-test-cflags  "${libj-test-cflags}")
string(REPLACE ";" " " libj-cxx11-cflags "${libj-cxx11-cflags}")

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

## bdw-gc
if(LIBJ_USE_BDWGC)
    add_subdirectory(deps/bdwgc)
endif(LIBJ_USE_BDWGC)

## convertutf
if(NOT LIBJ_USE_ICONV)
    add_subdirectory(deps/convertutf)
endif(NOT LIBJ_USE_ICONV)

## jscre
add_subdirectory(deps/jscre)

## nldtoa
add_subdirectory(deps/iv/iv/lv5/third_party/netlib_dtoa)

## v8dtoa
add_subdirectory(deps/iv/iv/lv5/third_party/v8_dtoa)

## gtest
if(LIBJ_BUILD_GTEST)
    add_subdirectory(deps/googletest)
endif(LIBJ_BUILD_GTEST)

## trace
if(UNIX AND LIBJ_TRACE)
    add_library(trace STATIC
        src/trace.cpp
    )

    target_link_libraries(trace
        dl
    )

    set_target_properties(trace PROPERTIES
        COMPILE_FLAGS ${libj-deps-cflags}
    )
endif(UNIX AND LIBJ_TRACE)

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

if(LIBJ_BUILD_TEST)
    add_subdirectory(gtest)
endif(LIBJ_BUILD_TEST)
