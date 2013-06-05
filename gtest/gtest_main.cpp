// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/trace.h>
#include <libj/typedef.h>
#include <libj/detail/debug_gc.h>

int main(int argc, char** argv) {
    LIBJ_DEBUG_TRACE_ON;
    LIBJ_DEBUG_TRACE_INCLUDE("^libj::(.*)::create");

    testing::InitGoogleTest(&argc, argv);
    int r = RUN_ALL_TESTS();

    LIBJ_DEBUG_GC;

    LIBJ_DEBUG_PRINT(
        "remaining objects: %d",
        LIBJ_DEBUG_OBJECT_COUNT);

    LIBJ_DEBUG_TRACE_OFF;
    return r;
}
