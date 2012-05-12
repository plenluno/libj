// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_OBJECT_H_
#define LIBJ_OBJECT_H_

#include <boost/utility.hpp>
#include "libj/type.h"
#include "libj/pointer.h"

namespace libj {

class String;

class Object
    : public ObjectBase
    , private boost::noncopyable {
 public:
    typedef LIBJ_CPTR(Object) CPtr;
    
    virtual TypeId type() const = 0;

    virtual bool instanceOf(TypeId id) const {
        return id == Type<Object>::id();
    }
    
    virtual Int compareTo(LIBJ_CPTR(Object) that) const {
        if (!that)
            return 1;
        TypeId thisId = this->type();
        TypeId thatId = that->type();
        if (thisId == thatId)
            return 0;
        else if (this->instanceOf(thatId))
            return 1;
        else if (that->instanceOf(thisId))
            return -1;
        else
            return thisId < thatId ? -1 : 1;
    }

    virtual LIBJ_CPTR(String) toString() const = 0;
};

}  // namespace libj

#endif  // LIBJ_OBJECT_H_
