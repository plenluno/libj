// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_SET_H_
#define LIBJ_SET_H_

#include <libj/collection.h>

namespace libj {

class Set : LIBJ_COLLECTION(Set)
 public:
    static Ptr create();
};

}  // namespace libj

#endif  // LIBJ_SET_H_
