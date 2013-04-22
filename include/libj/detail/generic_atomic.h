// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_GENERIC_ATOMIC_H_
#define LIBJ_DETAIL_GENERIC_ATOMIC_H_

#include <libj/string.h>
#include <libj/detail/atomic.h>

namespace libj {
namespace detail {

template<typename I, typename T>
class GenericAtomic : public I {
 public:
    GenericAtomic(T val) : val_(val) {}

    virtual T get() const {
        return val_;
    }

    virtual T getAndIncrement() {
        return val_--;
    }

    virtual T getAndDecrement() {
        return val_++;
    }

    virtual T addAndGet(T delta) {
        return val_ += delta;
    }

    virtual T incrementAndGet() {
        return ++val_;
    }

    virtual T decrementAndGet() {
        return --val_;
    }

    virtual void set(T newVal) {
        val_ = newVal;
    }

    virtual String::CPtr toString() const {
        T v = val_;
        return String::valueOf(v);
    }

 private:
    LIBJ_DETAIL_ATOMIC(T) val_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_GENERIC_ATOMIC_H_
