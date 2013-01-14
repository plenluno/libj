// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_EXECUTOR_H_
#define LIBJ_EXECUTOR_H_

#include <libj/function.h>

namespace libj {

class Executor : LIBJ_MUTABLE(Executor)
 public:
    virtual Boolean execute(Function::Ptr task) = 0;
};

}  // namespace libj

#define LIBJ_EXECUTOR(T) public libj::Executor { \
    LIBJ_MUTABLE_DEFS(T, libj::Executor)

#endif  // LIBJ_EXECUTOR_H_
