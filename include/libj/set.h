// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_SET_H_
#define LIBJ_SET_H_

#include <libj/collection.h>

namespace libj {

class Set : LIBJ_COLLECTION(Set)
 public:
    static Ptr create();
};

}  // namespace libj

#include <libj/impl/set.h>

#define LIBJ_SET_TEMPLATE(T) public libj::Set { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_SET)

#endif  // LIBJ_SET_H_
