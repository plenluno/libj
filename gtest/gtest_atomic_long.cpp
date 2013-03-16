// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/atomic_long.h>
#include <libj/js_function.h>
#include <libj/status.h>
#include <libj/thread.h>

namespace libj {

TEST(GTestAtomicLong, TestCreate) {
    AtomicLong::Ptr a1 = AtomicLong::create();
    AtomicLong::Ptr a2 = AtomicLong::create(5);
    ASSERT_TRUE(!!a1);
    ASSERT_TRUE(!!a2);
}

TEST(GTestAtomicLong, TestGet) {
    AtomicLong::Ptr a1 = AtomicLong::create();
    AtomicLong::Ptr a2 = AtomicLong::create(5);
    ASSERT_EQ(0, a1->get());
    ASSERT_EQ(5, a2->get());
}

TEST(GTestAtomicLong, TestSet) {
    AtomicLong::Ptr a = AtomicLong::create(5);
    a->set(11);
    ASSERT_EQ(11, a->get());
}

TEST(GTestAtomicLong, TestAddAndGet) {
    AtomicLong::Ptr a = AtomicLong::create(5);
    ASSERT_EQ(13, a->addAndGet(8));
}

TEST(GTestAtomicLong, TestIncrementAndGet) {
    AtomicLong::Ptr a = AtomicLong::create(5);
    ASSERT_EQ(6, a->incrementAndGet());
}

TEST(GTestAtomicLong, TestDecrementAndGet) {
    AtomicLong::Ptr a = AtomicLong::create(5);
    ASSERT_EQ(4, a->decrementAndGet());
}

class GTestAtomicLongInc : LIBJ_JS_FUNCTION(GTestAtomicLongInc)
 public:
    GTestAtomicLongInc(
        AtomicLong::Ptr a,
        Size max)
        : max_(max)
        , a_(a) {}

    virtual Value operator()(JsArray::Ptr args) {
        for (Size i = 0; i < max_; i++) {
            a_->incrementAndGet();
        }
        return Status::OK;
    }

 private:
    Size max_;
    AtomicLong::Ptr a_;
};

TEST(GTestAtomicLong, TestIncrementAndGet2) {
    AtomicLong::Ptr a = AtomicLong::create();

    Thread::Ptr t1 = Thread::create(
        Function::Ptr(new GTestAtomicLongInc(a, 1000)));
    Thread::Ptr t2 = Thread::create(
        Function::Ptr(new GTestAtomicLongInc(a, 1000)));
    Thread::Ptr t3 = Thread::create(
        Function::Ptr(new GTestAtomicLongInc(a, 1333)));

    t1->start();
    t2->start();
    t3->start();

    t1->join();
    t2->join();
    t3->join();

    ASSERT_EQ(3333, a->get());
}

}  // namespace libj
