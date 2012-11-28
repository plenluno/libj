// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_OBJECT_H_
#define LIBJ_OBJECT_H_

#include <libj/type.h>
#include <libj/detail/noncopyable.h>

namespace libj {

class String;

class Object
    : public detail::ObjectBase
    , private detail::NonCopyable {
 public:
    typedef LIBJ_CPTR(Object) CPtr;

    static CPtr null();

    virtual Boolean instanceof(TypeId id) const;

    virtual Int compareTo(CPtr that) const;

    virtual Boolean equals(CPtr that) const;

    virtual TypeId type() const = 0;

    virtual LIBJ_CPTR(String) toString() const = 0;
};

}  // namespace libj

#include <libj/impl/object.h>

#endif  // LIBJ_OBJECT_H_
