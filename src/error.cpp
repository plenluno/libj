// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"

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

#define LIBJ_ERROR_MSG_DECL_GEN(NAME, MESSAGE) \
    static const String::CPtr MSG_##NAME;

#define LIBJ_ERROR_MSG_CASE_GEN(NAME, MESSAGE) \
    case NAME: \
        msg = MSG_##NAME; \
        break;

class ErrorImpl : public Error {
 private:
    LIBJ_ERROR_MSG_MAP(LIBJ_ERROR_MSG_DECL_GEN)

 private:
    Status::CPtr status_;

    ErrorImpl(Int code, String::CPtr msg)
        : status_(Status::create(code, msg)) {}

 public:
    static CPtr create(Int code) {
        if (code < ANY || code >= END_OF_CODE) {
            return null();
        } else {
            String::CPtr msg;
            switch (code) {
                LIBJ_ERROR_MSG_MAP(LIBJ_ERROR_MSG_CASE_GEN)
            default:
                return null();
            }
            return CPtr(new ErrorImpl(code, msg));
        }
    }

    static CPtr create(Int code, String::CPtr msg) {
        if (code < ANY || code >= END_OF_CODE) {
            return null();
        } else {
            return CPtr(new ErrorImpl(code, msg));
        }
    }

    LIBJ_STATUS_IMPL(status_);
};

#define LIBJ_ERROR_MSG_DEF_GEN(NAME, MESSAGE) \
    const String::CPtr ErrorImpl::MSG_##NAME = String::create(MESSAGE);

LIBJ_ERROR_MSG_MAP(LIBJ_ERROR_MSG_DEF_GEN)

Error::CPtr Error::create(Int code) {
    return ErrorImpl::create(code);
}

Error::CPtr Error::create(Int code, String::CPtr msg) {
    return ErrorImpl::create(code, msg);
}

}  // namespace libj
