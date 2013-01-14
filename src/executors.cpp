// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/executors.h>
#include <libj/detail/executor_service.h>

namespace libj {
namespace executors {

ExecutorService::Ptr createFixedThreadPool(Size numThreads) {
    return ExecutorService::Ptr(
        new detail::ExecutorService<ExecutorService>(numThreads));
}

ExecutorService::Ptr createSingleThreadExecutor() {
    return createFixedThreadPool(1);
}

}  // namespace executors
}  // namespace libj
