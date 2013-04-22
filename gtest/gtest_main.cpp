// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/detail/gc_base.h>

#ifdef LIBJ_USE_BDWGC
    #include <gc.h>
#endif

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    int r = RUN_ALL_TESTS();

#ifdef LIBJ_USE_BDWGC
    GC_gcollect();
    GC_gcollect();
#endif

#ifdef LIBJ_DEBUG
    libj::console::debug(
        "[LIBJ DEBUG] remaining objects: %d",
        LIBJ_DEBUG_OBJECT_COUNT);
#endif

    return r;
}
