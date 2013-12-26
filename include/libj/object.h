// Copyright (c) 2012-2013 Plenluno All rights reserved.

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

    virtual Size hashCode() const;

    virtual Int compareTo(CPtr that) const;

    virtual Boolean equals(CPtr that) const;

    virtual Boolean instanceof(TypeId id) const;

    virtual TypeId type() const = 0;

    virtual LIBJ_CPTR(String) toString() const = 0;

    template<typename T> Boolean is() const;
};

}  // namespace libj

#include <libj/impl/object.h>

#endif  // LIBJ_OBJECT_H_
