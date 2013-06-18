// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_THREAD_H_
#define LIBJ_DETAIL_THREAD_H_

#include <libj/thread.h>
#include <libj/exception.h>

#ifdef LIBJ_USE_CXX11
# include <thread>
#else
# include <assert.h>
# include <pthread.h>
# include <signal.h>
#endif

namespace libj {
namespace detail {

class FunctionHolder {
 public:
    FunctionHolder(Function::Ptr f) : func_(f) {}

    void operator()() {
        (*func_)();
    }

 private:
    Function::Ptr func_;
};

#ifdef LIBJ_USE_CXX11

class Thread : public libj::Thread {
 public:
    Thread(Function::Ptr func)
        : thread_(NULL)
        , finish_(false)
        , func_(func) {}

    virtual ~Thread() {
        if (isAlive()) {
            thread_->detach();
        }
        delete thread_;
    }

    virtual void start() {
        if (thread_) {
            LIBJ_THROW(Error::ILLEGAL_STATE);
        } else {
            FunctionHolder holder(func_);
            thread_ = new std::thread(holder);
        }
    }

    virtual void join() {
        if (isAlive()) {
            thread_->join();
            finish_ = true;
        }
    }

    virtual String::CPtr toString() const {
        return String::create();
    }

 private:
    Boolean isAlive() const {
        return thread_ && !finish_;
    }

    std::thread* thread_;
    Boolean finish_;
    Function::Ptr func_;
};

#else  // LIBJ_USE_CXX11

class Thread : public libj::Thread {
 public:
    Thread(Function::Ptr func)
        : thread_(0)
        , start_(false)
        , finish_(false)
        , func_(func) {}

    virtual ~Thread() {
        if (isAlive()) {
            int r = pthread_detach(thread_);
            assert(!r);
        }
    }

    virtual void start() {
        if (start_) LIBJ_THROW(Error::ILLEGAL_STATE);

        FunctionHolder* holder = new FunctionHolder(func_);
        pthread_create(&thread_, NULL, &Thread::run, holder);
        start_ = true;
    }

    virtual void join() {
        if (isAlive()) {
            int r = pthread_join(thread_, NULL);
            assert(!r);
            finish_ = true;
        }
    }

    virtual String::CPtr toString() const {
        return String::create();
    }

 private:
    static void* run(void* arg) {
        FunctionHolder* holder = static_cast<FunctionHolder*>(arg);
        (*holder)();
        delete holder;
        return NULL;
    }

    Boolean isAlive() const {
        return start_ && !finish_;
    }

    pthread_t thread_;
    Boolean start_;
    Boolean finish_;
    Function::Ptr func_;
};

#endif  // LIBJ_USE_CXX11

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_THREAD_H_
