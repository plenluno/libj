// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_EXECUTOR_H_
#define LIBJ_EXECUTOR_H_

#include <libj/function.h>

namespace libj {

class Executor : LIBJ_MUTABLE(Executor)
 public:
    virtual Boolean execute(Function::Ptr task) = 0;
};

}  // namespace libj

#include <libj/impl/executor.h>

#define LIBJ_EXECUTOR(T) public libj::Executor { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_EXECUTOR)

#endif  // LIBJ_EXECUTOR_H_
