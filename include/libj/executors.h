// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_EXECUTORS_H_
#define LIBJ_EXECUTORS_H_

#include <libj/executor_service.h>

namespace libj {
namespace executors {

ExecutorService::Ptr createFixedThreadPool(Size numThreads);

ExecutorService::Ptr createSingleThreadExecutor();

}  // namespace executors
}  // namespace libj

#endif  // LIBJ_EXECUTORS_H_
