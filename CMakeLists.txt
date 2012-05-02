cmake_minimum_required(VERSION 2.8)

project(libj)

find_package(Boost)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "boost not found.")
endif()

find_library(GC gc REQUIRED)
if(NOT EXISTS ${GC})
    message(FATAL_ERROR "libgc not found.")
endif()

find_library(PTHREAD pthread REQUIRED)
if(NOT EXISTS ${PTHREAD})
    message(FATAL_ERROR "libpthread not found.")
endif()

find_library(GTEST gtest REQUIRED)
if(NOT EXISTS ${GTEST})
    message(FATAL_ERROR "libgtest not found.")
endif()

include_directories(
    include
    deps
    deps/cvtutf
)

link_directories(
    ${CMAKE_BINARY_DIR}
)

set(libj-src
    src/array_list.cpp
    src/error.cpp
    src/no_exceptions.cpp
    src/string.cpp
)

set(libj-deps
    cvtutf
)

# deps
add_library(cvtutf STATIC
    deps/cvtutf/ConvertUTF.c
)

# gtest
add_executable(libj-gtest
    gtest/gtest_array_list.cpp
    gtest/gtest_immutable.cpp
    gtest/gtest_main.cpp
    gtest/gtest_mutable.cpp
    gtest/gtest_null.cpp
    gtest/gtest_singleton.cpp
    gtest/gtest_string.cpp
    gtest/gtest_value.cpp
    ${libj-src}
)

target_link_libraries(libj-gtest
    gtest
    pthread
    ${libj-deps}
)

set_target_properties(libj-gtest
    PROPERTIES COMPILE_FLAGS "-DLIBJ_GTEST_BUILD_ERRORS")

# with shared_ptr
add_library(j-with-sp STATIC
    ${libj-src}
)

target_link_libraries(j-with-sp
    ${libj-deps}
)

set_target_properties(j-with-sp
    PROPERTIES COMPILE_FLAGS "-fno-rtti -fno-exceptions")

# with bdw gc
add_library(j-with-bdw-gc STATIC
    ${libj-src}
)

target_link_libraries(j-with-bdw-gc
    gc
    ${libj-deps}
)

set_target_properties(j-with-bdw-gc
    PROPERTIES COMPILE_FLAGS "-fno-rtti -fno-exceptions -DLIBJ_USE_BOEHM_GC")

