// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_GC_BASE_H_
#define LIBJ_GC_BASE_H_

#include "libj/config.h"

namespace libj {

#ifdef LIBJ_USE_BOEHM_GC
class GCBase : public gc_cleanup {
};
#else
class GCBase {
 protected:
    virtual ~GCBase() {}
};
#endif

}  // namespace libj

#endif  // LIBJ_GC_BASE_H_
