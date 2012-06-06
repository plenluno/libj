// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/status.h"
#include "libj/string.h"

namespace libj {

class StatusImpl : public Status {
 public:
    Int code() const {
        return code_;
    }

    String::CPtr toString() const {
        if (message_)
            return message_;
        else
            return String::create();
    }

 public:
    static CPtr create(Int code) {
        CPtr p(new StatusImpl(code));
        return p;
    }

    static CPtr create(Int code, String::CPtr msg) {
        Status::CPtr p(new StatusImpl(code, msg));
        return p;
    }

 private:
    Int code_;
    String::CPtr message_;

    StatusImpl(Int code)
        : code_(code)
        , message_(LIBJ_NULL(String)) {}

    StatusImpl(Int code, String::CPtr msg)
        : code_(code)
        , message_(msg) {}
};

Status::CPtr Status::create(Int code) {
    return StatusImpl::create(code);
}

Status::CPtr Status::create(Int code, String::CPtr msg) {
    return StatusImpl::create(code, msg);
}

}  // namespace libj
