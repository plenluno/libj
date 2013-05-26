# Copyright (c) 2013 Plenluno All rights reserved.

cmake_minimum_required(VERSION 2.8)

project(gtest)

set(libj-test-src
    gtest_array_list.cpp
    gtest_console.cpp
    gtest_cvtutf.cpp
    gtest_error.cpp
    gtest_function.cpp
    gtest_immutable.cpp
    gtest_json.cpp
    gtest_js_array.cpp
    gtest_js_array_buffer.cpp
    gtest_js_data_view.cpp
    gtest_js_date.cpp
    gtest_js_function.cpp
    gtest_js_object.cpp
    gtest_js_regexp.cpp
    gtest_linked_list.cpp
    gtest_main.cpp
    gtest_map.cpp
    gtest_math.cpp
    gtest_mutable.cpp
    gtest_set.cpp
    gtest_singleton.cpp
    gtest_status.cpp
    gtest_string.cpp
    gtest_string_buffer.cpp
    gtest_typed_array_list.cpp
    gtest_typed_js_array.cpp
    gtest_typed_linked_list.cpp
    gtest_typed_set.cpp
    gtest_typed_value_holder.cpp
    gtest_value.cpp
    gtest_value_holder.cpp
)

if(LIBJ_USE_CXX11)
    set(libj-test-src
        ${libj-test-src}
        gtest_js_closure.cpp
    )
endif(LIBJ_USE_CXX11)

if(LIBJ_USE_THREAD)
    set(libj-test-src
        ${libj-test-src}
        gtest_atomic_integer.cpp
        gtest_atomic_long.cpp
        gtest_blocking_linked_queue.cpp
        gtest_concurrent_linked_queue.cpp
        gtest_concurrent_map.cpp
        gtest_executor_service.cpp
        gtest_thread.cpp
    )
endif(LIBJ_USE_THREAD)

add_executable(libj-test
    ${libj-test-src}
)

target_link_libraries(libj-test
    ${libj-linklibs}
)

set_target_properties(libj-test PROPERTIES
    COMPILE_FLAGS "${libj-test-cflags}"
)
