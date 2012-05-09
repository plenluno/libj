// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_ERROR_H_
#define LIBJ_ERROR_H_

#include "libj/immutable.h"
#include "libj/string.h"

namespace libj {

class Error : LIBJ_IMMUTABLE(Error)
 public:
    enum Code {
        ANY,
        ILLEGAL_ARGUMENT,
        INDEX_OUT_OF_BOUNDS,
    };

    static CPtr create(Code code);
    static CPtr create(Code code, String::CPtr msg);

    virtual Code code() const = 0;
};

}  // namespace libj

#endif  // LIBJ_ERROR_H_