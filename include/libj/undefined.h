// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_UNDEFINED_H_
#define LIBJ_UNDEFINED_H_

#include "libj/singleton.h"
#include "libj/string.h"

namespace libj {

class Undefined : LIBJ_SINGLETON(Undefined)
 public:
    String::CPtr toString() const {
        return String::create("undefined");
    }
};

}  // namespace libj

#endif  // LIBJ_UNDEFINED_H_
