// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_ARRAY_BUFFER_H_
#define LIBJ_ARRAY_BUFFER_H_

#include "libj/mutable.h"

namespace libj {

class ArrayBuffer : LIBJ_MUTABLE(ArrayBuffer)
};

#define LIBJ_ARRAY_BUFFER(T) public libj::ArrayBuffer { \
    LIBJ_MUTABLE_DECLS(T, libj::ArrayBuffer)

}  // namespace libj

#endif  // LIBJ_ARRAY_BUFFER_H_
