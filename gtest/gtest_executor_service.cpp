// Copyright (c) 2013-2014 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/executors.h>
#include <libj/executor_service.h>
#include <libj/js_function.h>
#include <libj/status.h>
#include <libj/concurrent_linked_queue.h>

#ifdef LIBJ_PF_WINDOWS
# include <libj/platform/windows.h>
#else
# include <unistd.h>
#endif

namespace libj {

TEST(GTestExecutorService, TestCreateFixedThreadPool) {
    ExecutorService::Ptr es = executors::createFixedThreadPool(10);
    ASSERT_TRUE(!!es);
}

TEST(GTestExecutorService, TestCreateSingleThreadExecutor) {
    ExecutorService::Ptr es = executors::createSingleThreadExecutor();
    ASSERT_TRUE(!!es);
}

TEST(GTestExecutorService, TestInstanceOf) {
    ExecutorService::Ptr es = executors::createSingleThreadExecutor();
    ASSERT_TRUE(es->instanceof(Type<ExecutorService>::id()));
    ASSERT_TRUE(es->instanceof(Type<Executor>::id()));
    ASSERT_TRUE(es->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(es->instanceof(Type<Object>::id()));

    ASSERT_FALSE(es->instanceof(Type<Immutable>::id()));
}

class GTestESTask : LIBJ_JS_FUNCTION(GTestESTask)
 public:
    GTestESTask(
        UInt n,
        ConcurrentLinkedQueue::Ptr q)
        : n_(n)
        , q_(q) {}

    Value operator()(JsArray::Ptr args) {
        usleep(100000 * (n_ % 3));
        q_->offer(n_);
        console::log("task %d", n_);
        return Status::OK;
    }

 private:
    UInt n_;
    ConcurrentLinkedQueue::Ptr q_;
};

TEST(GTestExecutorService, TestExecuteAndAwaitTermination) {
    ExecutorService::Ptr es = executors::createFixedThreadPool(3);
    const Size n = 10;
    ConcurrentLinkedQueue::Ptr q = ConcurrentLinkedQueue::create();
    for (Size i = 0; i < n; i++) {
        es->execute(JsFunction::Ptr(new GTestESTask(i, q)));
    }
    es->shutdown();
    ASSERT_TRUE(es->awaitTermination());
    ASSERT_EQ(n, q->size());
}

}  // namespace libj
