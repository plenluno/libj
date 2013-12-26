// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_STATUS_H_
#define LIBJ_STATUS_H_

#include <libj/string.h>

namespace libj {

class Status : LIBJ_IMMUTABLE(Status)
 public:
    enum Code {
        OK
    };

    static CPtr create(Int code);

    static CPtr create(Int code, String::CPtr msg);

    virtual Int code() const = 0;

    virtual String::CPtr message() const = 0;
};

}  // namespace libj

#include <libj/impl/status.h>

#define LIBJ_STATUS(T) public libj::Status { \
    LIBJ_IMMUTABLE_DEFS(T, libj::Status)

#endif  // LIBJ_STATUS_H_
