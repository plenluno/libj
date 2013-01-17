// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/executors.h>
#include <libj/detail/executor_service.h>
#include <libj/detail/default_thread_factory.h>

namespace libj {
namespace executors {

ThreadFactory::Ptr defaultThreadFactory() {
    return ThreadFactory::Ptr(new detail::DefaultThreadFactory());
}

ExecutorService::Ptr createFixedThreadPool(
    Size numThreads,
    ThreadFactory::Ptr threadFactory) {
    if (threadFactory) {
        return ExecutorService::Ptr(
            new detail::ExecutorService<ExecutorService>(
                    numThreads,
                    threadFactory));
    } else {
        return ExecutorService::null();
    }
}

ExecutorService::Ptr createSingleThreadExecutor(
    ThreadFactory::Ptr threadFactory) {
    return createFixedThreadPool(1, threadFactory);
}

}  // namespace executors
}  // namespace libj
