// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_MUTABLE_H_
#define LIBJ_IMPL_MUTABLE_H_

#include <libj/cast.h>

namespace libj {

inline Mutable::Ptr Mutable::null() {
    static LIBJ_NULL_PTR_DEF(Mutable, nullp);
    return nullp;
}

inline Mutable::Ptr Mutable::self() {
    return LIBJ_STATIC_PTR_CAST(Mutable)(LIBJ_THIS);
}

inline Mutable::CPtr Mutable::celf() const {
    return LIBJ_STATIC_CPTR_CAST(Mutable)(LIBJ_THIS);
}

inline Boolean Mutable::instanceof(TypeId id) const {
    return id == Type<Mutable>::id()
        || Object::instanceof(id);
}

}  // namespace libj

#define LIBJ_MUTABLE_METHODS(T, B) public: \
    virtual libj::TypeId type() const { \
        return libj::Type<T >::id(); \
    } \
    virtual Boolean instanceof(libj::TypeId id) const { \
        return id == libj::Type<T >::id() \
            || B::instanceof(id); \
    }

#define LIBJ_MUTABLE_DEFS(T, B) public: \
    typedef LIBJ_PTR(T) Ptr; \
    typedef LIBJ_CPTR(T) CPtr; \
    LIBJ_MUTABLE_METHODS(T, B) \
    static Ptr null() { \
        static LIBJ_NULL_PTR_DEF(T, nullp); \
        return nullp; \
    }

#define LIBJ_MUTABLE_TEMPLATE_DEFS(T, B) public: \
    typedef LIBJ_PTR_TYPE(T) Ptr; \
    typedef LIBJ_CPTR_TYPE(T) CPtr; \
    LIBJ_MUTABLE_METHODS(T, B) \
    static Ptr null() { \
        static LIBJ_NULL_PTR_TYPE_DEF(T, nullp); \
        return nullp; \
    }

#endif  // LIBJ_IMPL_MUTABLE_H_
