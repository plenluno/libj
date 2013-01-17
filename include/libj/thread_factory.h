// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_THREAD_FACTORY_H_
#define LIBJ_THREAD_FACTORY_H_

#include <libj/thread.h>

namespace libj {

class ThreadFactory : LIBJ_MUTABLE(ThreadFactory)
 public:
    virtual Thread::Ptr createThread(Function::Ptr func) = 0;
};

}  // namespace libj

#endif  // LIBJ_THREAD_FACTORY_H_
