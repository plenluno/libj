// Copyright (c) 2013-2014 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/concurrent_linked_queue.h>
#include <libj/js_function.h>
#include <libj/error.h>
#include <libj/thread.h>

namespace libj {

TEST(GTestConcurrentLinkedQueue, TestInstanceOf) {
    ConcurrentLinkedQueue::Ptr q = ConcurrentLinkedQueue::create();
    ASSERT_TRUE(q->instanceof(Type<ConcurrentLinkedQueue>::id()));
    ASSERT_TRUE(q->instanceof(Type<Queue>::id()));
    ASSERT_TRUE(q->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(q->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(q->instanceof(Type<Object>::id()));

    ASSERT_FALSE(q->instanceof(Type<Immutable>::id()));
}

TEST(GTestConcurrentLinkedQueue, TestAddAndRemove) {
    const Size n = 1000;

    ConcurrentLinkedQueue::Ptr q = ConcurrentLinkedQueue::create();
    ASSERT_TRUE(q->isEmpty());

    for (Size i = 0; i < n; i++) {
        ASSERT_TRUE(q->add(i));
    }
    ASSERT_FALSE(q->isEmpty());

    for (Size i = 0; i < n; i++)  {
        Value v = q->remove();
        ASSERT_TRUE(v.equals(i));
    }
    ASSERT_TRUE(q->isEmpty());

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(q->remove());
#else
    ASSERT_EQ(Error::NO_SUCH_ELEMENT, toCPtr<Error>(q->remove())->code());
#endif
}

TEST(GTestConcurrentLinkedQueue, TestOfferAndPoll) {
    const Size n = 1000;

    ConcurrentLinkedQueue::Ptr q = ConcurrentLinkedQueue::create();
    ASSERT_TRUE(q->isEmpty());

    for (Size i = 0; i < n; i++) {
        ASSERT_TRUE(q->offer(i));
    }
    ASSERT_FALSE(q->isEmpty());

    for (Size i = 0; i < n; i++)  {
        Value v = q->poll();
        ASSERT_TRUE(v.equals(i));
    }
    ASSERT_TRUE(q->isEmpty());

    ASSERT_TRUE(q->poll().isUndefined());
}

class GTestCLQProducer : LIBJ_JS_FUNCTION(GTestCLQProducer)
 public:
    GTestCLQProducer(
        ConcurrentLinkedQueue::Ptr q,
        Size max)
        : max_(max)
        , queue_(q) {}

    virtual Value operator()(JsArray::Ptr args) {
        for (Size i = 0; i < max_; i++) {
            queue_->offer(i);
        }
        return Status::OK;
    }

 private:
    Size max_;
    ConcurrentLinkedQueue::Ptr queue_;
};

class GTestCLQConsumer : LIBJ_JS_FUNCTION(GTestCLQConsumer)
 public:
    GTestCLQConsumer(
        ConcurrentLinkedQueue::Ptr q)
        : count_(0)
        , queue_(q) {}

    Size count() const {
        return count_;
    }

    virtual Value operator()(JsArray::Ptr args) {
        while (!queue_->poll().isUndefined()) {
            count_++;
        }
        return Status::OK;
    }

 private:
    Size count_;
    ConcurrentLinkedQueue::Ptr queue_;
};

TEST(GTestConcurrentLinkedQueue, TestThreadSafe) {
    ConcurrentLinkedQueue::Ptr q = ConcurrentLinkedQueue::create();

    Thread::Ptr p1 = Thread::create(
        Function::Ptr(new GTestCLQProducer(q, 1000)));
    Thread::Ptr p2 = Thread::create(
        Function::Ptr(new GTestCLQProducer(q, 1000)));
    Thread::Ptr p3 = Thread::create(
        Function::Ptr(new GTestCLQProducer(q, 100)));

    GTestCLQConsumer::Ptr cf1(new GTestCLQConsumer(q));
    GTestCLQConsumer::Ptr cf2(new GTestCLQConsumer(q));
    GTestCLQConsumer::Ptr cf3(new GTestCLQConsumer(q));
    Thread::Ptr c1 = Thread::create(cf1);
    Thread::Ptr c2 = Thread::create(cf2);
    Thread::Ptr c3 = Thread::create(cf3);

    p1->start();
    p2->start();
    p3->start();
    c1->start();
    c2->start();

    p1->join();
    p2->join();
    p3->join();
    c1->join();
    c2->join();

    c3->start();
    c3->join();

    // console::log("consumer1: %d", cf1->count());
    // console::log("consumer2: %d", cf2->count());
    // console::log("consumer3: %d", cf3->count());
    ASSERT_TRUE(q->isEmpty());
    ASSERT_EQ(2100, cf1->count() + cf2->count() + cf3->count());
}

}  // namespace libj
