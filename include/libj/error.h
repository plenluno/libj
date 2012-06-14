// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_ERROR_H_
#define LIBJ_ERROR_H_

#include "libj/status.h"

namespace libj {

class Error : LIBJ_STATUS(Error)
 public:
    enum Code {
        ANY = 1,
        TIMEOUT,
        ILLEGAL_ARGUMENT,
        ILLEGAL_DATA_FORMAT,
        ILLEGAL_REQUEST,
        ILLEGAL_RESPONSE,
        ILLEGAL_STATE,
        ILLEGAL_TYPE,
        INDEX_OUT_OF_BOUNDS,
        NO_SUCH_ELEMENT,
        NO_SUCH_FIELD,
        NO_SUCH_METHOD,
        NULL_POINTER,
        UNSUPPORTED_VERSION,
        UNSUPPORTED_OPERATION,
    };

    static CPtr create(Int code);
    static CPtr create(Int code, String::CPtr msg);
};

}  // namespace libj

#endif  // LIBJ_ERROR_H_
