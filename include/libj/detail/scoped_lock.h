// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_SCOPED_LOCK_H_
#define LIBJ_DETAIL_SCOPED_LOCK_H_

#include <libj/detail/mutex.h>

namespace libj {
namespace detail {

class ScopedLock : private NonCopyable {
 public:
    ScopedLock(Mutex* mutex) : mutex_(mutex) {
        assert(mutex_);
        mutex_->lock();
    }

    ~ScopedLock() {
        mutex_->unlock();
    }

 private:
    Mutex* mutex_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_SCOPED_LOCK_H_
