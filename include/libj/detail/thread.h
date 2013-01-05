// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_THREAD_H_
#define LIBJ_DETAIL_THREAD_H_

#include <libj/thread.h>

#include <assert.h>
#include <pthread.h>

namespace libj {
namespace detail {

class Thread : public libj::Thread {
 public:
    Thread(Function::Ptr func)
        : thread_(0)
        , func_(func) {}

    virtual ~Thread() {
        if (isAlive()) {
            int r = pthread_detach(thread_);
            assert(!r);
        }
    }

    virtual void start() {
        FunctionHolder* holder = new FunctionHolder(func_);
        pthread_create(&thread_, NULL, &Thread::run, holder);
    }

    virtual void join() {
        if (isAlive()) {
            int r = pthread_join(thread_, NULL);
            assert(!r);
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
        return !pthread_kill(thread_, 0);
    }

    pthread_t thread_;
    Function::Ptr func_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_THREAD_H_
