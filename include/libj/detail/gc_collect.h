// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GC_COLLECT_H_
#define LIBJ_DETAIL_GC_COLLECT_H_

#include <libj/detail/gc_base.h>

#ifdef LIBJ_USE_BDWGC

namespace libj {
namespace detail {

#ifdef LIBJ_DEBUG

inline void gcollect() {
    static LIBJ_COUNT_T count(static_cast<Long>(0));
    LIBJ_DEBUG_PRINT("full-gc: %d", ++count);

    Long before;
    Long after;
    do {
        before = LIBJ_DEBUG_OBJECT_COUNT;
        GC_gcollect();
        after = LIBJ_DEBUG_OBJECT_COUNT;
    } while (before > after);
}

#else   // LIBJ_DEBUG

inline void gcollect() {
    GC_gcollect();
}

#endif  // LIBJ_DEBUG

}  // namespace detail
}  // namespace libj

#define LIBJ_GC_COLLECT libj::detail::gcollect()

#define LIBJ_GC_COLLECT_PER(N) { \
    static LIBJ_COUNT_T count(static_cast<Long>(0)); \
    if (++count >= N) { \
        LIBJ_GC_COLLECT; \
        count = 0; \
    } \
}

#endif

#else   // LIBJ_USE_BDWGC

#define LIBJ_GC_COLLECT

#define LIBJ_GC_COLLECT_PER(N)

#endif  // LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_GC_COLLECT_H_
