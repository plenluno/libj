// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_MUTEX_H_
#define LIBJ_DETAIL_MUTEX_H_

#include <pthread.h>

namespace libj {
namespace detail {

class Mutex {
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
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_MUTEX_H_
