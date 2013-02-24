// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_IMMUTABLE_H_
#define LIBJ_IMPL_IMMUTABLE_H_

#include <libj/cast.h>

namespace libj {

inline Immutable::CPtr Immutable::null() {
    static LIBJ_NULL_CPTR_DEF(Immutable, nullp);
    return nullp;
}

inline Immutable::CPtr Immutable::self() const {
    return LIBJ_STATIC_CPTR_CAST(Immutable)(LIBJ_THIS);
}

inline Boolean Immutable::instanceof(TypeId id) const {
    return id == Type<Immutable>::id()
        || Object::instanceof(id);
}

}  // namespace libj

#define LIBJ_IMMUTABLE_METHODS(T, B) public: \
    virtual libj::TypeId type() const { \
        return libj::Type<T>::id(); \
    } \
    virtual Boolean instanceof(libj::TypeId id) const { \
        return id == libj::Type<T>::id() \
            || B::instanceof(id); \
    }

#define LIBJ_IMMUTABLE_DEFS(T, B) public: \
    typedef LIBJ_CPTR(T) CPtr; \
    LIBJ_IMMUTABLE_METHODS(T, B) \
    static CPtr null() { \
        LIBJ_NULL_CPTR_DEF(T, nullp); \
        return nullp; \
    }

#define LIBJ_IMMUTABLE_TEMPLATE_DEFS(T, B) public: \
    typedef LIBJ_CPTR_TYPE(T) CPtr; \
    LIBJ_IMMUTABLE_METHODS(T, B) \
    static CPtr null() { \
        LIBJ_NULL_CPTR_TYPE_DEF(T, nullp); \
        return nullp; \
    }

#endif  // LIBJ_IMPL_IMMUTABLE_H_
