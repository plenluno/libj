// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_EXECUTORS_H_
#define LIBJ_EXECUTORS_H_

#include <libj/executor_service.h>
#include <libj/thread_factory.h>

namespace libj {
namespace executors {

ThreadFactory::Ptr defaultThreadFactory();

ExecutorService::Ptr createFixedThreadPool(
    Size numThreads,
    ThreadFactory::Ptr threadFactory = defaultThreadFactory());

ExecutorService::Ptr createSingleThreadExecutor(
    ThreadFactory::Ptr threadFactory = defaultThreadFactory());

}  // namespace executors
}  // namespace libj

#endif  // LIBJ_EXECUTORS_H_
