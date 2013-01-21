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

class Condition;

#ifdef LIBJ_USE_CXX11

class Mutex : private NonCopyable {
 public:
    Boolean lock() {
        mutex_.lock();
        return true;
    }

    Boolean unlock() {
        mutex_.unlock();
        return false;
    }

 private:
    std::mutex mutex_;

    friend class Condition;
};

#else  // LIBJ_USE_CXX11

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
