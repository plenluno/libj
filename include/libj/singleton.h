// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_SINGLETON_H_
#define LIBJ_SINGLETON_H_

#include "libj/object.h"

namespace libj {

class Singleton
    : public Object
    , public SingletonBase {
 public:
    typedef LIBJ_PTR(Singleton) Ptr;
    typedef LIBJ_CPTR(Singleton) CPtr;

    static Ptr null();
};

}  // namespace libj

#include "./detail/singleton.h"

#define LIBJ_SINGLETON(T) LIBJ_SINGLETON_DEFS(T)

#endif  // LIBJ_SINGLETON_H_
