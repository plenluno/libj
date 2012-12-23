cmake_minimum_required(VERSION 2.8)

project(libj)

include(CMakeDependentOption)

# options ------------------------------------------------------------------------------------------

option(LIBJ_USE_CXX11 "Use C++11" OFF)
option(LIBJ_USE_BDW_GC "Use BDW-GC" OFF)
option(LIBJ_USE_EXCEPTION "Use Exceptions" OFF)
option(LIBJ_USE_JSONCPP "Use JsonCpp" OFF)
option(LIBJ_BUILD_GTEST "Build Google Tests" OFF)

cmake_dependent_option(LIBJ_BUILD_BDW_GC "Build BDW-GC" ON "LIBJ_USE_BDW_GC" OFF)

message(STATUS "LIBJ_USE_BDW_GC=${LIBJ_USE_BDW_GC}")
message(STATUS "LIBJ_USE_CXX11=${LIBJ_USE_CXX11}")
message(STATUS "LIBJ_USE_EXCEPTION=${LIBJ_USE_EXCEPTION}")
message(STATUS "LIBJ_USE_JSONCPP=${LIBJ_USE_JSONCPP}")
message(STATUS "LIBJ_BUILD_BDW_GC=${LIBJ_BUILD_BDW_GC}")
message(STATUS "LIBJ_BUILD_GTEST=${LIBJ_BUILD_GTEST}")

# find libraries -----------------------------------------------------------------------------------

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

# variables ----------------------------------------------------------------------------------------

set(libj-include
    include
    deps
    deps/iv
)

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
    src/symbol.cpp
    src/value_holder.cpp
)

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

set(libj-deps
    cvtutf
    dtoa
    json
    ndtoa
    regexp
)

if(APPLE)
    set(libj-deps
        ${libj-deps}
        iconv
    )
endif(APPLE)

if(LIBJ_USE_BDW_GC)
    set(libj-deps
        ${libj-deps}
        gc
    )
endif(LIBJ_USE_BDW_GC)

set(libj-cflags
    -Wall
    -fno-rtti
)

set(libj-deps-cflags
    -fno-rtti
)

if(LIBJ_USE_CXX11)
    set(libj-cflags
        ${libj-cflags}
        --std=c++0x
    )
    set(libj-deps-cflags
        ${libj-deps-cflags}
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
string(REPLACE ";" " " libj-deps-cflags "${libj-deps-cflags}")

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
if(LIBJ_BUILD_BDW_GC)
    add_custom_command(
        TARGET json PRE_BUILD
        COMMAND rsync -av ${CMAKE_CURRENT_LIST_DIR}/deps/bdwgc ${CMAKE_BINARY_DIR}/deps/
        COMMAND rsync -av ${CMAKE_CURRENT_LIST_DIR}/deps/libatomic_ops ${CMAKE_BINARY_DIR}/deps/bdwgc/
        COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && ./autogen.sh
        COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && ./configure
        COMMAND cd ${CMAKE_BINARY_DIR}/deps/bdwgc && make
        COMMAND ln -sf ${CMAKE_BINARY_DIR}/deps/bdwgc/.libs/libgc.a ${CMAKE_BINARY_DIR}/libgc.a
    )
endif(LIBJ_BUILD_BDW_GC)

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
