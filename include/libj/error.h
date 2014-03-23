// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_ERROR_H_
#define LIBJ_ERROR_H_

#include <libj/status.h>

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
        EMPTY_COLLECTION,
        REJECTED_EXECUTION,
    };

    static CPtr create(Code code);

    static CPtr create(Code code, String::CPtr msg);
};

}  // namespace libj

#include <assert.h>
#include <libj/impl/error.h>

#define LIBJ_ERROR(T) public libj::Error { \
    LIBJ_IMMUTABLE_DEFS(T, LIBJ_ERROR)

#ifndef LIBJ_USE_EXCEPTION
#define LIBJ_THROW(code) assert(false);
#define LIBJ_HANDLE_ERROR(code) return libj::Error::create(code);
#endif

#endif  // LIBJ_ERROR_H_
