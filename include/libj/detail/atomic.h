// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_ATOMIC_H_
#define LIBJ_DETAIL_ATOMIC_H_

#include <libj/string.h>

#ifdef LIBJ_USE_CXX11
    #include <atomic>
#else
    #include <boost/atomic.hpp>
#endif

namespace libj {
namespace detail {

template<typename I, typename T>
class Atomic : public I {
 public:
    Atomic(T val) : val_(val) {}

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
#ifdef LIBJ_USE_CXX11
    std::atomic<T> val_;
#else
    boost::atomic<T> val_;
#endif
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_ATOMIC_H_
