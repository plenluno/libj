// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GC_BASE_H_
#define LIBJ_DETAIL_GC_BASE_H_

#include <libj/config.h>

#ifdef LIBJ_DEBUG
    #include <libj/typedef.h>
#ifdef LIBJ_USE_THREAD
    #include <libj/detail/atomic.h>
    #define LIBJ_DEBUG_COUNT_T LIBJ_DETAIL_ATOMIC(libj::Long)
#else
    #define LIBJ_DEBUG_COUNT_T libj::Long
#endif
    #define LIBJ_DEBUG_OBJECT_COUNT     libj::detail::GCBase::count(0)
    #define LIBJ_DEBUG_OBJECT_COUNT_INC libj::detail::GCBase::count(1)
    #define LIBJ_DEBUG_OBJECT_COUNT_DEC libj::detail::GCBase::count(-1)
    #define LIBJ_DEBUG_OBJECT_COUNT_DEF public: \
        static libj::Long count(libj::Long diff) { \
            static LIBJ_DEBUG_COUNT_T cnt(static_cast<Long>(0)); \
            cnt += diff; \
            return cnt; \
        }
#else
    #define LIBJ_DEBUG_OBJECT_COUNT
    #define LIBJ_DEBUG_OBJECT_COUNT_INC
    #define LIBJ_DEBUG_OBJECT_COUNT_DEC
    #define LIBJ_DEBUG_OBJECT_COUNT_DEF
#endif

#ifdef LIBJ_USE_BDWGC

namespace libj {
namespace detail {

class GCBase : virtual public gc {
 public:
    GCBase() {
        GC_finalization_proc oldProc;
        void* oldData;
        void* base = GC_base(this);
        if (base) {
            GC_register_finalizer_no_order(
                base,
                cleanup,
                reinterpret_cast<void*>(
                    reinterpret_cast<char*>(this) -
                    reinterpret_cast<char*>(base)),
                &oldProc,
                &oldData);
            if (oldProc) {
                GC_register_finalizer_no_order(
                    base,
                    oldProc,
                    oldData,
                    NULL,
                    NULL);
            }
        }
        LIBJ_DEBUG_OBJECT_COUNT_INC;
    }

    virtual ~GCBase() {
        GC_register_finalizer_no_order(
            GC_base(this),
            NULL,
            NULL,
            NULL,
            NULL);
        LIBJ_DEBUG_OBJECT_COUNT_DEC;
    }

 private:
    static void GC_cdecl cleanup(void* obj, void* displ) {
        (reinterpret_cast<GCBase*>(
            reinterpret_cast<char*>(obj) +
            reinterpret_cast<ptrdiff_t>(displ)))->~GCBase();
    }

    LIBJ_DEBUG_OBJECT_COUNT_DEF;
};

}  // namespace detail
}  // namespace libj

#else  // LIBJ_USE_BDWGC

#ifndef LIBJ_USE_CXX11
    #include <boost/enable_shared_from_this.hpp>
    #define LIBJ_ENABLE_THIS(T) boost::enable_shared_from_this<T>
#else
    #include <memory>
    #define LIBJ_ENABLE_THIS(T) std::enable_shared_from_this<T>
#endif

namespace libj {
namespace detail {

class GCBase : public LIBJ_ENABLE_THIS(GCBase) {
 protected:
    GCBase() {
        LIBJ_DEBUG_OBJECT_COUNT_INC;
    }

    virtual ~GCBase() {
        LIBJ_DEBUG_OBJECT_COUNT_DEC;
    }

    LIBJ_DEBUG_OBJECT_COUNT_DEF;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_GC_BASE_H_
