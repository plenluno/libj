// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_OBJECT_H_
#define LIBJ_OBJECT_H_

#include <boost/utility.hpp>
#include "libj/type.h"
#include "libj/pointer.h"

namespace libj {

class String;

class ObjectBase : private boost::noncopyable {
 public:
    virtual TypeId type() const = 0;

    virtual bool instanceOf(TypeId id) const {
        return id == Type<Object>::id();
    }

    virtual LIBJ_CPTR(String) toString() const = 0;
};

}  // namespace libj

#endif  // LIBJ_OBJECT_H_
