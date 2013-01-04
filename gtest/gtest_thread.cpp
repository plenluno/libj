// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/js_function.h>
#include <libj/status.h>
#include <libj/thread.h>

#include <unistd.h>

namespace libj {

class GTestThreadFunc : LIBJ_JS_FUNCTION(GTestThreadFunc)
 public:
    GTestThreadFunc(UInt id) : id_(id) {}

    Value operator()(JsArray::Ptr args) {
        sleep(id_ % 2);
        console::log("run %d", id_);
        return Status::OK;
    }

 private:
    UInt id_;
};

TEST(GTestThread, TestCreate) {
    Thread::Ptr th = Thread::create(JsFunction::null());
    ASSERT_TRUE(!th);

    th = Thread::create(Function::Ptr(new GTestThreadFunc(0)));
    ASSERT_TRUE(!!th);
}

TEST(GTestThread, TestStart) {
    Thread::Ptr th = Thread::create(Function::Ptr(new GTestThreadFunc(9)));
    th->start();
}

TEST(GTestThread, TestStartAndJoin) {
    const Size n = 9;

    JsArray::Ptr threads = JsArray::create();
    for (Size i = 0; i < n; i++) {
        threads->add(Thread::create(Function::Ptr(new GTestThreadFunc(i))));
    }

    for (Size i = 0; i < n; i++) {
        threads->getPtr<Thread>(i)->start();
    }

    for (Size i = 0; i < n; i++) {
        threads->getPtr<Thread>(i)->join();
    }
}

}  // namespace libj
