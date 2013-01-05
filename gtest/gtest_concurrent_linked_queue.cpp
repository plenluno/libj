// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/concurrent_linked_queue.h>
#include <libj/js_function.h>
#include <libj/error.h>
#include <libj/thread.h>

#include <unistd.h>

namespace libj {

TEST(GTestConcurrentLinkedQueue, TestAddAndRemove) {
    const Size n = 10000;

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

    ASSERT_EQ(Error::NO_SUCH_ELEMENT, toCPtr<Error>(q->remove())->code());
}

TEST(GTestConcurrentLinkedQueue, TestOfferAndPoll) {
    const Size n = 10000;

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

    Value operator()(JsArray::Ptr args) {
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

    Value operator()(JsArray::Ptr args) {
        usleep(10000);
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
        Function::Ptr(new GTestCLQProducer(q, 100000)));
    Thread::Ptr p2 = Thread::create(
        Function::Ptr(new GTestCLQProducer(q, 100000)));

    GTestCLQConsumer::Ptr cf1(new GTestCLQConsumer(q));
    GTestCLQConsumer::Ptr cf2(new GTestCLQConsumer(q));
    Thread::Ptr c1 = Thread::create(cf1);
    Thread::Ptr c2 = Thread::create(cf2);

    p1->start();
    p2->start();
    c1->start();
    c2->start();

    p1->join();
    p2->join();
    c1->join();
    c2->join();

    console::log("consumer1: %d", cf1->count());
    console::log("consumer2: %d", cf2->count());
    ASSERT_EQ(200000, cf1->count() + cf2->count());
}

}  // namespace libj
