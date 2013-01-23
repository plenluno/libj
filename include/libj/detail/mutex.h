// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_MUTEX_H_
#define LIBJ_DETAIL_MUTEX_H_

#include <libj/config.h>
#include <libj/detail/noncopyable.h>

#ifdef LIBJ_USE_CXX11
    #include <mutex>
#else
    #include <assert.h>
    #include <pthread.h>
#endif

namespace libj {
namespace detail {

#ifdef LIBJ_USE_CXX11

class ScopedLock;

class Mutex : private NonCopyable {
 public:
    Boolean lock() {
        mutex_.lock();
        return true;
    }

    Boolean unlock() {
        mutex_.unlock();
        return true;
    }

 private:
    std::mutex mutex_;

    friend class ScopedLock;
};

#else  // LIBJ_USE_CXX11

class Condition;

class Mutex : private NonCopyable {
 public:
    Mutex() {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~Mutex() {
        int r = pthread_mutex_destroy(&mutex_);
        assert(!r);
    }

    Boolean lock() {
        return !pthread_mutex_lock(&mutex_);
    }

    Boolean unlock() {
        return !pthread_mutex_unlock(&mutex_);
    }

 private:
    pthread_mutex_t mutex_;

    friend class Condition;
};

#endif  // LIBJ_USE_CXX11

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_MUTEX_H_
