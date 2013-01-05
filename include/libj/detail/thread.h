// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_THREAD_H_
#define LIBJ_DETAIL_THREAD_H_

#include <libj/thread.h>
#include <libj/exception.h>

#include <assert.h>
#include <pthread.h>
#include <signal.h>

namespace libj {
namespace detail {

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
            finish_ = true;
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
        // TODO(plenluno): implement
        return String::create();
    }

 private:
    class FunctionHolder {
     public:
        FunctionHolder(Function::Ptr f) : func(f) {}

        Function::Ptr func;
    };

    static void* run(void* arg) {
        FunctionHolder* holder = static_cast<FunctionHolder*>(arg);
        (*holder->func)();
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

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_THREAD_H_
