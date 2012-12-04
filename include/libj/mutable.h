// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_MUTABLE_H_
#define LIBJ_MUTABLE_H_

#include <libj/object.h>
#include <libj/detail/gc_base.h>

namespace libj {

class Mutable
    : public Object
    , public detail::GCBase
    , public detail::MutableBase {
 public:
    typedef LIBJ_PTR(Mutable) Ptr;
    typedef LIBJ_CPTR(Mutable) CPtr;

    static Ptr null();

    virtual Boolean instanceof(TypeId id) const;
};

}  // namespace libj

#include <libj/impl/mutable.h>

#define LIBJ_MUTABLE(T) public libj::Mutable { \
    LIBJ_MUTABLE_DEFS(T, libj::Mutable)

#define LIBJ_MUTABLE_TEMPLATE(T) public libj::Mutable { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, libj::Mutable)

#endif  // LIBJ_MUTABLE_H_
