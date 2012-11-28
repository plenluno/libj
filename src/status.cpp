// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/status.h>
#include <libj/detail/status.h>

namespace libj {

Status::CPtr Status::create(Int code) {
    LIBJ_STATIC_SYMBOL_DEF(symOK, "OK");

    String::CPtr msg;
    if (code == OK) {
        msg = symOK;
    } else {
        msg = String::null();
    }
    return CPtr(new detail::Status<Status>(code, msg));
}

Status::CPtr Status::create(Int code, String::CPtr msg) {
    return CPtr(new detail::Status<Status>(code, msg));
}

}  // namespace libj
