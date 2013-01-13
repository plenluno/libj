// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_CONDITION_H_
#define LIBJ_DETAIL_CONDITION_H_

#include <libj/detail/mutex.h>

namespace libj {
namespace detail {

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

    void wait(Mutex* mutex) {
        pthread_cond_wait(&cond_, &(mutex->mutex_));
    }

 private:
    pthread_cond_t cond_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_CONDITION_H_
