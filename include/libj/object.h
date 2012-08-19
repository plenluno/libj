// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_OBJECT_H_
#define LIBJ_OBJECT_H_

#include <boost/utility.hpp>

#include "libj/type.h"

namespace libj {

class String;

class Object
    : public ObjectBase
    , private boost::noncopyable {
 public:
    typedef LIBJ_CPTR(Object) CPtr;

    virtual TypeId type() const = 0;

    virtual Boolean instanceof(TypeId id) const {
        return id == Type<Object>::id();
    }

    virtual Int compareTo(LIBJ_CPTR(Object) that) const {
        if (!that) return TYPE_CMP_NA;

        TypeId thisId = this->type();
        TypeId thatId = that->type();
        if (thisId == thatId) {
            Int diff = static_cast<const Object*>(this) - &(*that);
            if (diff < 0) {
                return -TYPE_CMP_SAME;
            } else if (diff > 0) {
                return TYPE_CMP_SAME;
            } else {
                return 0;
            }
        } else if (this->instanceof(thatId)) {
            return TYPE_CMP_DERIVED;
        } else if (that->instanceof(thisId)) {
            return -TYPE_CMP_DERIVED;
        } else {
            return thisId < thatId
                    ? -TYPE_CMP_NOT_DERIVED
                    : TYPE_CMP_NOT_DERIVED;
        }
    }

    virtual Boolean equals(LIBJ_CPTR(Object) that) const {
        return !compareTo(that);
    }

    virtual LIBJ_CPTR(String) toString() const = 0;
};

}  // namespace libj

#endif  // LIBJ_OBJECT_H_
