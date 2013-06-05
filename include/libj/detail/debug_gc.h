// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_DEBUG_GC_H_
#define LIBJ_DETAIL_DEBUG_GC_H_

#include <libj/detail/gc_base.h>

#ifdef LIBJ_USE_BDWGC

namespace libj {
namespace detail {

void gcollect() {
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

#define LIBJ_DEBUG_GC libj::detail::gcollect()

#else  // LIBJ_USE_BDWGC

#define LIBJ_DEBUG_GC

#endif  // LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_DEBUG_GC_H_
