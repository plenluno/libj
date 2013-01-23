// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_SCOPED_LOCK_H_
#define LIBJ_DETAIL_SCOPED_LOCK_H_

#include <libj/detail/mutex.h>

namespace libj {
namespace detail {

class Condition;

#ifdef LIBJ_USE_CXX11

class ScopedLock : private NonCopyable {
 public:
    ScopedLock(Mutex& mutex) : lock_(mutex.mutex_) {}

 private:
    std::unique_lock<std::mutex> lock_;

    friend class Condition;
};

#else  // LIBJ_USE_CXX11

class ScopedLock : private NonCopyable {
 public:
    ScopedLock(Mutex& mutex) : mutex_(mutex) {
        mutex_.lock();
    }

    ~ScopedLock() {
        mutex_.unlock();
    }

 private:
    Mutex& mutex_;

    friend class Condition;
};

#endif  // LIBJ_USE_CXX11

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_SCOPED_LOCK_H_
