// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GC_BASE_H_
#define LIBJ_DETAIL_GC_BASE_H_

#include <libj/config.h>

namespace libj {
namespace detail {

#ifdef LIBJ_USE_BDWGC
class GCBase : public gc_cleanup {
};
#else
class GCBase {
 protected:
    virtual ~GCBase() {}
};
#endif

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GC_BASE_H_
