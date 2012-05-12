// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"
#include "libj/string.h"

namespace libj {

class ErrorImpl : public Error {
 public:
    Code code() const {
        return code_;
    }
    
    String::CPtr toString() const {
        return String::create();
    }
    
 public:
    static CPtr create() {
        CPtr p(new ErrorImpl());
        return p;
    }

    static CPtr create(Code code) {
        CPtr p(new ErrorImpl(code));
        return p;
    }
    
    static CPtr create(Code code, String::CPtr msg) {
        Error::CPtr p(new ErrorImpl(code, msg));
        return p;
    }
    
 private:
    Code code_;
    String::CPtr message_;
    
    ErrorImpl()
        : code_(Error::ANY)
        , message_(static_cast<String*>(0)) {}
    
    ErrorImpl(Code code)
        : code_(code)
        , message_(static_cast<String*>(0)) {}
    
    ErrorImpl(Code code, String::CPtr msg)
        : code_(code)
        , message_(msg) {}
};

Error::CPtr Error::create() {
    return ErrorImpl::create();
}

Error::CPtr Error::create(Code code) {
    return ErrorImpl::create(code);
}

Error::CPtr Error::create(Code code, String::CPtr msg) {
    return ErrorImpl::create(code, msg);
}

}  // namespace libj
