// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_MUTABLE_H_
#define LIBJ_TYPED_MUTABLE_H_

#include <libj/mutable.h>

namespace libj {

template<typename T>
class TypedMutable {
 public:
    virtual ~TypedMutable() {}
};

}  // namespace libj

#endif  // LIBJ_TYPED_MUTABLE_H_
