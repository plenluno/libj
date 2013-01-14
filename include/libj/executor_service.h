// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_EXECUTOR_SERVICE_H_
#define LIBJ_EXECUTOR_SERVICE_H_

#include <libj/executor.h>

namespace libj {

class ExecutorService : LIBJ_EXECUTOR(ExecutorService)
 public:
    virtual Boolean awaitTermination() = 0;

    virtual Boolean isShutdown() const = 0;

    virtual Boolean isTerminated() const = 0;

    virtual void shutdown() = 0;
};

}  // namespace libj

#endif  // LIBJ_EXECUTOR_SERVICE_H_
