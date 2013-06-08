// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GC_COLLECT_H_
#define LIBJ_DETAIL_GC_COLLECT_H_

#include <libj/detail/gc_base.h>

#ifdef LIBJ_USE_BDWGC

namespace libj {
namespace detail {

inline void gcollect() {
    static LIBJ_COUNT_T cnt(static_cast<Long>(0));
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

#define LIBJ_GC_COLLECT libj::detail::gcollect()

#else   // LIBJ_USE_BDWGC

#define LIBJ_GC_COLLECT

#endif  // LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_GC_COLLECT_H_
