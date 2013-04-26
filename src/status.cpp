// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/status.h>
#include <libj/detail/status.h>

namespace libj {

Status::CPtr Status::create(Int code) {
    LIBJ_STATIC_CONST_STRING_DEF(strOK, "OK");

    String::CPtr msg;
    if (code == OK) {
        msg = strOK;
    } else {
        msg = String::null();
    }
    return CPtr(new detail::Status<Status>(code, msg));
}

Status::CPtr Status::create(Int code, String::CPtr msg) {
    return CPtr(new detail::Status<Status>(code, msg));
}

}  // namespace libj
