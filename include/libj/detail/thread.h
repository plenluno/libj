// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_THREAD_H_
#define LIBJ_DETAIL_THREAD_H_

#include <pthread.h>

namespace libj {
namespace detail {

template<typename I>
class Thread : public I {
 public:
    Thread(Function::Ptr func) : func_(func) {}

    virtual void start() {
        pthread_create(&thread_, NULL, &Thread::run, this);
    }

    virtual void join() {
        pthread_join(thread_, NULL);
    }

    virtual String::CPtr toString() const {
        // TODO(plenluno): implement
        return String::create();
    }

 private:
    static void* run(void* arg) {
        Thread* self = static_cast<Thread*>(arg);
        (*self->func_)();
        return NULL;
    }

    pthread_t thread_;
    Function::Ptr func_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_THREAD_H_
