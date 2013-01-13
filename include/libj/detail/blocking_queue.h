// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_BLOCKING_QUEUE_H_
#define LIBJ_DETAIL_BLOCKING_QUEUE_H_

#include <libj/exception.h>
#include <libj/detail/condition.h>
#include <libj/detail/scoped_lock.h>

namespace libj {
namespace detail {

template<typename I>
class BlockingQueue : public I {
 public:
    BlockingQueue(Size capacity = 0)  // '0' means unlimited
        : capacity_(capacity) {}

    virtual Boolean add(const Value& v) {
        if (offer(v)) {
            return true;
        } else {
            LIBJ_THROW(Error::ILLEGAL_STATE);
            return false;
        }
    }

    virtual Boolean addTyped(const Value& v) {
        return add(v);
    }

    virtual void clear() {
        ScopedLock lock(&mutex_);
        I::clear();
        notFull_.notifyAll();
    }

    virtual Value element() const {
        ScopedLock lock(const_cast<Mutex*>(&mutex_));
        if (I::size()) {
            return I::get(0);
        } else {
            LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
        }
    }

    virtual Iterator::Ptr iterator() const {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return Iterator::null();
    }

    virtual TypedIterator<Value>::Ptr iteratorTyped() const {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return TypedIterator<Value>::null();
    }

    virtual Boolean offer(const Value& v) {
        ScopedLock lock(&mutex_);
        if (isFull()) {
            return false;
        } else {
            Boolean success = I::add(v);
            assert(success);
            notEmpty_.notifyAll();
            return true;
        }
    }

    virtual Value peek() const {
        ScopedLock lock(const_cast<Mutex*>(&mutex_));
        if (I::size()) {
            return I::get(0);
        } else {
            return UNDEFINED;
        }
    }

    virtual Value poll() {
        ScopedLock lock(&mutex_);
        if (I::size()) {
            Value v = I::poll();
            notFull_.notifyAll();
            return v;
        } else {
            return UNDEFINED;
        }
    }

    virtual void put(const Value& v) {
        ScopedLock lock(&mutex_);
        while (isFull()) {
            notFull_.wait(&mutex_);
        }

        I::add(v);
        notEmpty_.notifyAll();
    }

    virtual Value remove() {
        ScopedLock lock(&mutex_);
        if (I::size()) {
            Value v = I::poll();
            notFull_.notifyAll();
            return v;
        } else {
            LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
        }
    }

    virtual Value remove(Size i) {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return UNDEFINED;
    }

    virtual Boolean remove(const Value& v) {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return false;
    }

    virtual Boolean removeTyped(const Value& v) {
        return remove(v);
    }

    virtual Value take() {
        ScopedLock lock(&mutex_);
        while (!I::size()) {
            notEmpty_.wait(&mutex_);
        }

        Value v = I::poll();
        notFull_.notifyAll();
        return v;
    }

 private:
    Boolean isFull() const {
        return !!capacity_ && I::size() == capacity_;
    }

 private:
    Size capacity_;
    Mutex mutex_;
    Condition notEmpty_;
    Condition notFull_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_BLOCKING_QUEUE_H_
