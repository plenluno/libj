// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_DEBUG_GC_H_
#define LIBJ_DETAIL_DEBUG_GC_H_

#include <libj/detail/gc_base.h>

#if defined(LIBJ_DEBUG) && defined(LIBJ_USE_BDWGC)

namespace libj {
namespace detail {

inline void runFullGC() {
    static LIBJ_DEBUG_COUNT_T cnt(static_cast<Long>(0));
    LIBJ_DEBUG_PRINT("full-gc: %d", ++cnt);

    Long before;
    Long after;
    do {
        before = LIBJ_DEBUG_OBJECT_COUNT;
        GC_gcollect();
        after = LIBJ_DEBUG_OBJECT_COUNT;
    } while (before > after);
}

}  // namespace detail
}  // namespace libj

#define LIBJ_DEBUG_GC libj::detail::runFullGC()

#else   // LIBJ_DEBUG && LIBJ_USE_BDWGC

#define LIBJ_DEBUG_GC

#endif  // LIBJ_DEBUG && LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_DEBUG_GC_H_
