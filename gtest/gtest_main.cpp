// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/debug.h>
#include <libj/trace.h>
#include <libj/detail/gc_base.h>

int main(int argc, char** argv) {
#ifdef LIBJ_DEBUG
    libj::trace::include("libj");
    libj::trace::exclude("libj::detail");
#endif

    testing::InitGoogleTest(&argc, argv);
    int r = RUN_ALL_TESTS();

#ifdef LIBJ_USE_BDWGC
    libj::Long before;
    libj::Long after;
    do {
        before = LIBJ_DEBUG_OBJECT_COUNT;
        GC_gcollect();
        after = LIBJ_DEBUG_OBJECT_COUNT;
    } while (before > after);
#endif

    LIBJ_DEBUG_PRINT(
        "remaining objects: %d",
        LIBJ_DEBUG_OBJECT_COUNT);
    return r;
}
