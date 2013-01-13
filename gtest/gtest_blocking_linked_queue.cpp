// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/console.h>
#include <libj/blocking_linked_queue.h>
#include <libj/js_function.h>
#include <libj/error.h>
#include <libj/thread.h>

namespace libj {

TEST(GTestBlockingLinkedQueue, TestAddAndRemove) {
    const Size n = 1000;

    BlockingLinkedQueue::Ptr q = BlockingLinkedQueue::create();
    ASSERT_TRUE(q->isEmpty());

    for (Size i = 0; i < n; i++) {
        ASSERT_TRUE(q->add(i));
    }
    ASSERT_EQ(n, q->size());
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

TEST(GTestBlockingLinkedQueue, TestOfferAndPoll) {
    const Size n = 1000;

    BlockingLinkedQueue::Ptr q = BlockingLinkedQueue::create();
    ASSERT_TRUE(q->isEmpty());

    for (Size i = 0; i < n; i++) {
        ASSERT_TRUE(q->offer(i));
    }
    ASSERT_EQ(n, q->size());
    ASSERT_FALSE(q->isEmpty());

    for (Size i = 0; i < n; i++)  {
        Value v = q->poll();
        ASSERT_TRUE(v.equals(i));
    }
    ASSERT_TRUE(q->isEmpty());

    ASSERT_TRUE(q->poll().isUndefined());
}

TEST(GTestBlockingLinkedQueue, TestCapacity) {
    const Size n = 10;

    BlockingLinkedQueue::Ptr q = BlockingLinkedQueue::create(n);
    ASSERT_TRUE(q->isEmpty());

    for (Size i = 0; i < n; i++) {
        ASSERT_TRUE(q->offer(i));
    }
    ASSERT_EQ(n, q->size());

    ASSERT_FALSE(q->offer(n));
    ASSERT_EQ(n, q->size());

    q->clear();
    ASSERT_TRUE(q->isEmpty());

    ASSERT_TRUE(q->poll().isUndefined());
}

class GTestBLQProducer : LIBJ_JS_FUNCTION(GTestBLQProducer)
 public:
    GTestBLQProducer(
        BlockingLinkedQueue::Ptr q,
        Size max)
        : max_(max)
        , queue_(q) {}

    Value operator()(JsArray::Ptr args) {
        for (Size i = 0; i < max_; i++) {
            queue_->put(i);
        }
        return Status::OK;
    }

 private:
    Size max_;
    BlockingLinkedQueue::Ptr queue_;
};

class GTestBLQConsumer : LIBJ_JS_FUNCTION(GTestBLQConsumer)
 public:
    GTestBLQConsumer(
        BlockingLinkedQueue::Ptr q,
        Size max)
        : max_(max)
        , count_(0)
        , queue_(q) {}

    Size count() const {
        return count_;
    }

    Value operator()(JsArray::Ptr args) {
        while (count_ < max_) {
            queue_->take();
            count_++;
        }
        return Status::OK;
    }

 private:
    Size max_;
    Size count_;
    BlockingLinkedQueue::Ptr queue_;
};

TEST(GTestBlockingLinkedQueue, TestPutAndTake) {
    BlockingLinkedQueue::Ptr q = BlockingLinkedQueue::create(100);

    Thread::Ptr p1 = Thread::create(
        Function::Ptr(new GTestBLQProducer(q, 1000)));
    Thread::Ptr p2 = Thread::create(
        Function::Ptr(new GTestBLQProducer(q, 1000)));
    Thread::Ptr p3 = Thread::create(
        Function::Ptr(new GTestBLQProducer(q, 100)));

    GTestBLQConsumer::Ptr cf1(new GTestBLQConsumer(q, 700));
    GTestBLQConsumer::Ptr cf2(new GTestBLQConsumer(q, 700));
    GTestBLQConsumer::Ptr cf3(new GTestBLQConsumer(q, 700));
    Thread::Ptr c1 = Thread::create(cf1);
    Thread::Ptr c2 = Thread::create(cf2);
    Thread::Ptr c3 = Thread::create(cf3);

    p1->start();
    p2->start();
    p3->start();
    c1->start();
    c2->start();
    c3->start();

    p1->join();
    p2->join();
    p3->join();
    c1->join();
    c2->join();
    c3->join();

    // console::log("consumer1: %d", cf1->count());
    // console::log("consumer2: %d", cf2->count());
    // console::log("consumer3: %d", cf3->count());
    ASSERT_TRUE(q->isEmpty());
    ASSERT_EQ(2100, cf1->count() + cf2->count() + cf3->count());
}

}  // namespace libj
