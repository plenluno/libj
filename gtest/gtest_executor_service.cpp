// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/executors.h>
#include <libj/executor_service.h>
#include <libj/js_function.h>
#include <libj/status.h>

#include <unistd.h>

namespace libj {

TEST(GTestExecutorService, TestCreateFixedThreadPool) {
    ExecutorService::Ptr es = executors::createFixedThreadPool(10);
    ASSERT_TRUE(!!es);
}

TEST(GTestExecutorService, TestCreateSingleThreadExecutor) {
    ExecutorService::Ptr es = executors::createSingleThreadExecutor();
    ASSERT_TRUE(!!es);
}

class GTestESTask : LIBJ_JS_FUNCTION(GTestESTask)
 public:
    GTestESTask(
        UInt n,
        JsArray::Ptr a)
        : n_(n)
        , ary_(a) {}

    Value operator()(JsArray::Ptr args) {
        usleep(100000 * (n_ % 5));
        ary_->add(n_);
        console::printf(console::NORMAL, "task %d\n", n_);
        return Status::OK;
    }

 private:
    UInt n_;
    JsArray::Ptr ary_;
};

TEST(GTestExecutorService, TestExecuteAndAwaitTermination) {
    ExecutorService::Ptr es = executors::createFixedThreadPool(3);
    const Size n = 10;
    JsArray::Ptr ary = JsArray::create();
    for (Size i = 0; i < n; i++) {
        es->execute(JsFunction::Ptr(new GTestESTask(i, ary)));
    }
    es->shutdown();
    ASSERT_TRUE(es->awaitTermination());
    ASSERT_EQ(n, ary->length());
}

}  // namespace libj
