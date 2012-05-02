// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_ERROR_H_
#define LIBJ_ERROR_H_

#include "libj/immutable.h"
#include "libj/string.h"

namespace libj {

class Error : LIBJ_IMMUTABLE(Error)
 public:
    enum Code {
        ANY,
        INDEX_OUT_OF_BOUNDS,
    };

    static Cptr create(Code code);
    static Cptr create(Code code, Type<String>::Cptr msg);

    virtual Code code() const = 0;
};

}  // namespace libj

#endif  // LIBJ_ERROR_H_