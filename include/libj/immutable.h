// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMMUTABLE_H_
#define LIBJ_IMMUTABLE_H_

#include "libj/gc_base.h"
#include "libj/object.h"

namespace libj {

class Immutable
    : public Object
    , public GCBase
    , public ImmutableBase {
 public:
    typedef LIBJ_CPTR(Immutable) CPtr;

    static CPtr null() {
        LIBJ_NULL_CPTR_DEF(Immutable, nullp);
        return nullp;
    }

    Boolean instanceof(TypeId id) const {
        return id == Type<Immutable>::id()
            || Object::instanceof(id);
    }
};

#define LIBJ_IMMUTABLE_METHODS(T, B) public: \
    libj::TypeId type() const { \
        return libj::Type<T>::id(); \
    } \
    Boolean instanceof(libj::TypeId id) const { \
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

#define LIBJ_IMMUTABLE(T) public libj::Immutable { \
    LIBJ_IMMUTABLE_DEFS(T, libj::Immutable)

}  // namespace libj

#endif  // LIBJ_IMMUTABLE_H_
