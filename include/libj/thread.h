// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_THREAD_H_
#define LIBJ_THREAD_H_

#include <libj/function.h>

namespace libj {

class Thread : LIBJ_MUTABLE(Thread)
 public:
    static Ptr create(Function::Ptr func);

    virtual void join() = 0;

    virtual void start() = 0;
};

}  // namespace libj

#endif  // LIBJ_THREAD_H_
