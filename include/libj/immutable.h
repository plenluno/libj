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

    static CPtr null();

    Boolean instanceof(TypeId id) const;
};

}  // namespace libj

#include "./detail/immutable.h"

#define LIBJ_IMMUTABLE(T) public libj::Immutable { \
    LIBJ_IMMUTABLE_DEFS(T, libj::Immutable)

#endif  // LIBJ_IMMUTABLE_H_
