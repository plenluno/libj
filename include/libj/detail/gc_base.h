// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GC_BASE_H_
#define LIBJ_DETAIL_GC_BASE_H_

#include <libj/config.h>

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
    }

    virtual ~GCBase() {
        GC_register_finalizer_no_order(
            GC_base(this),
            NULL,
            NULL,
            NULL,
            NULL);
    }

 private:
    static void GC_cdecl cleanup(void* obj, void* displ) {
        (reinterpret_cast<GCBase*>(
            reinterpret_cast<char*>(obj) +
            reinterpret_cast<ptrdiff_t>(displ)))->~GCBase();
    }
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
    virtual ~GCBase() {}
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_USE_BDWGC

#endif  // LIBJ_DETAIL_GC_BASE_H_
