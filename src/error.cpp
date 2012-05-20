// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"

namespace libj {

class ErrorImpl : public Error {
 private:
    Status::CPtr status_;
    
    ErrorImpl(Int code)
        : status_(Status::create(code)) {}
    
    ErrorImpl(Int code, String::CPtr msg)
        : status_(Status::create(code, msg)) {}
 
 public:
     static CPtr create(Int code) {
         CPtr p(new ErrorImpl(code));
         return p;
     }
     
     static CPtr create(Int code, String::CPtr msg) {
         CPtr p(new ErrorImpl(code, msg));
         return p;
     }
     
     LIBJ_STATUS_IMPL(status_);
};

Error::CPtr Error::create(Int code) {
    return ErrorImpl::create(code);
}

Error::CPtr Error::create(Int code, String::CPtr msg) {
    return ErrorImpl::create(code, msg);
}

}
