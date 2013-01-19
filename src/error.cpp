// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/error.h>
#include <libj/detail/status.h>

namespace libj {

#define LIBJ_ERROR_MSG_MAP(GEN) \
    GEN(ANY, "") \
    GEN(TIMEOUT, "Timeout") \
    GEN(ILLEGAL_ARGUMENT, "Illegal Argument") \
    GEN(ILLEGAL_DATA_FORMAT, "Illegal Data Format") \
    GEN(ILLEGAL_REQUEST, "Illegal Request") \
    GEN(ILLEGAL_RESPONSE, "Illegal Response") \
    GEN(ILLEGAL_STATE, "Illegal State") \
    GEN(ILLEGAL_TYPE, "Illegal Type") \
    GEN(INDEX_OUT_OF_BOUNDS, "Index Out Of Bounds") \
    GEN(NO_SUCH_ELEMENT, "No Such Element") \
    GEN(NO_SUCH_FIELD, "No Such Field") \
    GEN(NO_SUCH_METHOD, "No Such Method") \
    GEN(NULL_POINTER, "Null Pointer") \
    GEN(UNSUPPORTED_VERSION, "Unsupported Version") \
    GEN(UNSUPPORTED_OPERATION, "Unsupported Operation")

#define LIBJ_ERROR_MSG_DEF_GEN(NAME, MESSAGE) \
    const String::CPtr MSG_##NAME = String::create(MESSAGE);

#define LIBJ_ERROR_MSG_CASE_GEN(NAME, MESSAGE) \
    case NAME: \
        msg = MSG_##NAME; \
        break;

Error::CPtr Error::create(Error::Code code) {
    LIBJ_ERROR_MSG_MAP(LIBJ_ERROR_MSG_DEF_GEN);

    String::CPtr msg;
    switch (code) {
        LIBJ_ERROR_MSG_MAP(LIBJ_ERROR_MSG_CASE_GEN);
    default:
        msg = String::null();
    }
    return CPtr(new detail::Status<Error>(code, msg));
}

Error::CPtr Error::create(Error::Code code, String::CPtr msg) {
    return CPtr(new detail::Status<Error>(code, msg));
}

}  // namespace libj
