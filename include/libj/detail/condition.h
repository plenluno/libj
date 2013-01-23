// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_CONDITION_H_
#define LIBJ_DETAIL_CONDITION_H_

#include <libj/detail/scoped_lock.h>

#ifdef LIBJ_USE_CXX11
    #include <condition_variable>
#endif

namespace libj {
namespace detail {

#ifdef LIBJ_USE_CXX11

class Condition : private NonCopyable {
 public:
    void notify() {
        cond_.notify_one();
    }

    void notifyAll() {
        cond_.notify_all();
    }

    void wait(ScopedLock& lock) {
        cond_.wait(lock.lock_);
    }

 private:
    std::condition_variable cond_;
};

#else  // LIBJ_USE_CXX11

class Condition : private NonCopyable {
 public:
    Condition() {
        pthread_cond_init(&cond_, NULL);
    }

    virtual ~Condition() {
        pthread_cond_destroy(&cond_);
    }

    void notify() {
        pthread_cond_signal(&cond_);
    }

    void notifyAll() {
        pthread_cond_broadcast(&cond_);
    }

    void wait(ScopedLock& lock) {
        pthread_cond_wait(&cond_, &(lock.mutex_.mutex_));
    }

 private:
    pthread_cond_t cond_;
};

#endif  // LIBJ_USE_CXX11

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_CONDITION_H_
