// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_INPUT_STREAM_H_
#define LIBJ_INPUT_STRESM_H_

#include "libj/mutable.h"

namespace libj {

class InputStream : LIBJ_MUTABLE(InputStream)
 public:
    virtual Int read(Byte b[], Size off, Size len) = 0;
    virtual void close() = 0;
};

#define LIBJ_INPUT_STREAM(T) public libj::InputStream { \
    LIBJ_MUTABLE_DECLS_WITHOUT_CREATE(T, libj::InputStream)

}  // namespace libj

#endif  // LIBJ_INPUT_STREAM_H_