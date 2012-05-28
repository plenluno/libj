// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_STATUS_H_
#define LIBJ_STATUS_H_

#include "libj/immutable.h"
#include "libj/string.h"

namespace libj {

class Status : LIBJ_IMMUTABLE_WITHOUT_CREATE(Status)
 public:
    enum Code {
        OK
    };

    static CPtr create(Int code);
    static CPtr create(Int code, String::CPtr msg);

    virtual Int code() const = 0;
};

#define LIBJ_STATUS(T) public libj::Status { \
    LIBJ_IMMUTABLE_DECLS_WITHOUT_CREATE(T, libj::Status)

#define LIBJ_STATUS_IMPL(S) \
public: \
    Int code() const { \
        return S->code(); \
    } \
    String::CPtr toString() const { \
        return S->toString(); \
    }

}  // namespace libj

#endif  // LIBJ_STATUS_H_
