// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/error.h"
#include "libj/string.h"

namespace libj {

class ErrorImpl : public Error {
 public:
    Code code() const {
        return code_;
    }
    
    Type<String>::Cptr toString() const {
        return String::create();
    }
    
 public:
    static Cptr create() {
        Cptr p(new ErrorImpl());
        return p;
    }

    static Cptr create(Code code) {
        Cptr p(new ErrorImpl(code));
        return p;
    }
    
    static Cptr create(Code code, Type<String>::Cptr msg) {
        Type<Error>::Cptr p(new ErrorImpl(code, msg));
        return p;
    }
    
 private:
    Code code_;
    Type<String>::Cptr message_;
    
    ErrorImpl()
        : code_(Error::ANY)
        , message_(static_cast<String*>(0)) {}
    
    ErrorImpl(Code code)
        : code_(code)
        , message_(static_cast<String*>(0)) {}
    
    ErrorImpl(Code code, Type<String>::Cptr msg)
        : code_(code)
        , message_(msg) {}
};

Type<Error>::Cptr Error::create() {
    return ErrorImpl::create();
}

Type<Error>::Cptr Error::create(Code code) {
    return ErrorImpl::create(code);
}

Type<Error>::Cptr Error::create(Code code, Type<String>::Cptr msg) {
    return ErrorImpl::create(code, msg);
}

}  // namespace libj
