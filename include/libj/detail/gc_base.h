// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GC_BASE_H_
#define LIBJ_DETAIL_GC_BASE_H_

#include <libj/config.h>

#ifdef LIBJ_USE_BDWGC

namespace libj {
namespace detail {

class GCBase : public gc_cleanup {
};

}  // namespace detail
}  // namespace libj

#else  // LIBJ_USE_BDWGC

#ifdef LIBJ_USE_CXX11
    #include <memory>
    #define LIBJ_ENABLE_THIS(T) std::enable_shared_from_this<T>
#else
    #include <boost/enable_shared_from_this.hpp>
    #define LIBJ_ENABLE_THIS(T) boost::enable_shared_from_this<T>
#endif

namespace libj {
namespace detail {

class GCBase : public LIBJ_ENABLE_THIS(GCBase) {
 protected:
    virtual ~GCBase() {}
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_GC_BASE_H_
