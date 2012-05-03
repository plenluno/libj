// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_CONSOLE_H_
#define LIBJ_CONSOLE_H_

#include "libj/singleton.h"

namespace libj {

class Console : LIBJ_SINGLETON(Console)
 public:
    void log(Value val);
};

}  // namespace libj

#endif  // LIBJ_CONSOLE_H_