// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_SET_H_
#define LIBJ_SET_H_

#include "libj/collection.h"

namespace libj {

class Set : LIBJ_COLLECTION(Set)
 public:
     virtual bool add(Type<Object>::Ptr obj) = 0;
     virtual bool remove(Type<Object>::Ptr obj) = 0;
};

}  // namespace libj

#endif  // LIBJ_LIST_H_
