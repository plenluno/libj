// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_EXECUTOR_SERVICE_H_
#define LIBJ_DETAIL_EXECUTOR_SERVICE_H_

#include <libj/console.h>
#include <libj/function.h>
#include <libj/exception.h>
#include <libj/thread_factory.h>
#include <libj/blocking_linked_queue.h>
#include <libj/detail/scoped_lock.h>

namespace libj {
namespace detail {

template<typename I>
class ExecutorService : public I {
 public:
    ExecutorService(
        Size numThreads,
        ThreadFactory::Ptr threadFactory)
        : shutdown_(false)
        , workers_(ArrayList::create())
        , threads_(ArrayList::create())
        , channel_(BlockingLinkedQueue::create()) {
        assert(threadFactory);
        for (Size i = 0; i < numThreads; i++) {
            typename Worker::Ptr worker(new Worker(channel_));
            workers_->add(worker);

            Thread::Ptr thread = threadFactory->createThread(worker);
            threads_->add(thread);
            thread->start();
        }
    }

    virtual ~ExecutorService() {
        if (!isShutdown()) {
            shutdown();
        }
        awaitTermination();
    }

    virtual Boolean awaitTermination() {
        if (!isShutdown()) return false;

        Size len = threads_->length();
        for (Size i = 0; i < len; i++) {
            toPtr<Thread>(threads_->get(i))->join();
        }
        assert(channel_->isEmpty());
        return true;
    }

    virtual Boolean execute(Function::Ptr task) {
        ScopedLock lock(&mutex_);

        if (isShutdown()) {
#ifdef LIBJ_USE_EXCEPTION
            LIBJ_THROW(libj::Error::REJECTED_EXECUTION);
#endif
            return false;
        } else {
            channel_->put(task);
            return true;
        }
    }

    virtual Boolean isShutdown() const {
        return shutdown_;
    }

    virtual Boolean isTerminated() const {
        if (!isShutdown()) return false;

        Size len = workers_->length();
        for (Size i = 0; i < len; i++) {
            if (!toPtr<Worker>(workers_->get(i))->isTerminated()) {
                return false;
            }
        }
        return true;
    }

    virtual void shutdown() {
        ScopedLock lock(&mutex_);

        if (isShutdown()) return;

        shutdown_ = true;
        Size len = workers_->length();
        for (Size i = 0; i < len; i++) {
            channel_->put(typename Terminator::Ptr(new Terminator()));
        }
    }

    virtual String::CPtr toString() const {
        return String::create();
    }

 private:
    class Worker : LIBJ_FUNCTION_TEMPLATE(Worker)
        Worker(BlockingQueue::Ptr channel)
            : alive_(true)
            , channel_(channel) {}

        Boolean isTerminated() const {
            return !alive_;
        }

        virtual Value operator()(ArrayList::Ptr args) {
            while (alive_) {
                Value val = channel_->take();
                if (toPtr<Terminator>(val)) {
                    break;
                } else {
                    Function::Ptr task = toPtr<Function>(val);
                    assert(task);
#ifdef LIBJ_USE_EXCEPTION
                    try {
                        (*task)();
                    } catch(const libj::Exception& e) {
                        libj::console::error(e.message());
                    }
#else
                    (*task)();
#endif
                }
            }
            alive_ = false;
            return libj::Status::OK;
        }

        virtual String::CPtr toString() const {
            return String::create();
        }

     private:
        Boolean alive_;
        BlockingQueue::Ptr channel_;
    };

    class Terminator : LIBJ_FUNCTION_TEMPLATE(Terminator)
        virtual Value operator()(ArrayList::Ptr args) {
            return libj::Status::OK;
        }

        virtual String::CPtr toString() const {
            return String::create();
        }
    };

 private:
    Mutex mutex_;
    Boolean shutdown_;
    List::Ptr workers_;
    List::Ptr threads_;
    BlockingQueue::Ptr channel_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_EXECUTOR_SERVICE_H_
