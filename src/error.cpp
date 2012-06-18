// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"

namespace libj {

class ErrorImpl : public Error {
 private:
    Status::CPtr status_;

    ErrorImpl(Int code, String::CPtr msg)
        : status_(Status::create(code, msg)) {}

 public:
    static CPtr create(Int code) {
        if (code < ANY || code >= END_OF_CODE) {
            LIBJ_NULL_CPTR(Error, nullp);
            return nullp;
        } else {
            // TODO(plenluno): default messages
            LIBJ_NULL_CPTR(String, nullp);
            CPtr p(new ErrorImpl(code, nullp));
            return p;
        }
    }

    static CPtr create(Int code, String::CPtr msg) {
        if (code < ANY || code >= END_OF_CODE) {
            LIBJ_NULL_CPTR(Error, nullp);
            return nullp;
        } else {
            CPtr p(new ErrorImpl(code, msg));
            return p;
        }
    }

    LIBJ_STATUS_IMPL(status_);
};

Error::CPtr Error::create(Int code) {
    return ErrorImpl::create(code);
}

Error::CPtr Error::create(Int code, String::CPtr msg) {
    return ErrorImpl::create(code, msg);
}

}  // namespace libj
