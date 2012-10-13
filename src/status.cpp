// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/status.h"
#include "libj/string.h"

namespace libj {

class StatusImpl : public Status {
 public:
    Int code() const {
        return code_;
    }

    String::CPtr message() const {
        if (message_) {
            return message_;
        } else {
            return String::create();
        }
    }

    String::CPtr toString() const {
        return message();
    }

 public:
    static CPtr create(Int code) {
        String::CPtr msg;
        if (code == OK) {
            msg = String::create("OK");
        } else {
            msg = String::null();
        }
        return CPtr(new StatusImpl(code, msg));
    }

    static CPtr create(Int code, String::CPtr msg) {
        return CPtr(new StatusImpl(code, msg));
    }

 private:
    Int code_;
    String::CPtr message_;

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
