// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMMUTABLE_H_
#define LIBJ_IMMUTABLE_H_

#include "libj/value.h"
#include "libj/object.h"
#include "libj/gc_base.h"

namespace libj {

class ImmutableBase
    : public Immutable
    , public GCBase
    , public ObjectBase {
 public:
    bool instanceOf(TypeId id) const {
        return id == Type<Immutable>::id()
            || ObjectBase::instanceOf(id);
    }
};

#define LIBJ_IMMUTABLE_DECLS(T, B) public: \
    typedef LIBJ_CPTR(T) Cptr; \
    static Cptr create(); \
    libj::TypeId type() const { \
        return libj::Type<T>::id(); \
    } \
    bool instanceOf(libj::TypeId id) const { \
        return id == libj::Type<T>::id() \
            || B::instanceOf(id); \
    }

#define LIBJ_IMMUTABLE(T) public libj::ImmutableBase { \
    LIBJ_IMMUTABLE_DECLS(T, libj::ImmutableBase)

}  // namespace libj

#endif  // LIBJ_IMMUTABLE_H_
