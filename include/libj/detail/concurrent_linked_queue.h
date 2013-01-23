// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_CONCURRENT_LINKED_QUEUE_H_
#define LIBJ_DETAIL_CONCURRENT_LINKED_QUEUE_H_

#include <libj/exception.h>

#ifdef LIBJ_USE_LOCKFREE

#include <libj/detail/generic_collection.h>

#include <boost/lockfree/queue.hpp>

namespace libj {
namespace detail {

template<typename I>
class ConcurrentLinkedQueue : public GenericCollection<Value, I> {
 public:
    ConcurrentLinkedQueue()
        : queue_(128) {
        assert(queue_.is_lock_free());
    }

    virtual Boolean add(const Value& v) {
        if (queue_.push(v)) {
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
        Value v;
        while (queue_.pop(v)) {}
    }

    virtual Value element() const {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return UNDEFINED;
    }

    virtual Boolean isEmpty() const {
        return queue_.empty();
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
        return queue_.push(v);
    }

    virtual Value peek() const {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return UNDEFINED;
    }

    virtual Value poll() {
        Value v;
        queue_.pop(v);
        return v;
    }

    virtual Value remove() {
        Value v;
        if (queue_.pop(v)) {
            return v;
        } else {
            LIBJ_HANDLE_ERROR(Error::NO_SUCH_ELEMENT);
        }
    }

    virtual Boolean remove(const Value& v) {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return false;
    }

    virtual Boolean removeTyped(const Value& v) {
        return remove(v);
    }

    virtual Size size() const {
        LIBJ_THROW(Error::UNSUPPORTED_OPERATION);
        return 0;
    }

 private:
    mutable boost::lockfree::queue<Value> queue_;
};

}  // namespace detail
}  // namespace libj

#else  // LIBJ_USE_LOCKFREE

#include <libj/detail/linked_list.h>
#include <libj/detail/scoped_lock.h>

namespace libj {
namespace detail {

template<typename I>
class ConcurrentLinkedQueue : public LinkedList<I> {
 public:
    virtual Boolean add(const Value& v) {
        ScopedLock lock(mutex_);
        return LinkedList<I>::add(v);
    }

    virtual Boolean addTyped(const Value& v) {
        return add(v);
    }

    virtual void clear() {
        ScopedLock lock(mutex_);
        LinkedList<I>::clear();
    }

    virtual Value element() const {
        ScopedLock lock(mutex_);
        if (LinkedList<I>::size()) {
            return LinkedList<I>::get(0);
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
        return add(v);
    }

    virtual Value peek() const {
        ScopedLock lock(mutex_);
        if (LinkedList<I>::size()) {
            return LinkedList<I>::get(0);
        } else {
            return UNDEFINED;
        }
    }

    virtual Value poll() {
        ScopedLock lock(mutex_);
        return LinkedList<I>::poll();
    }

    virtual Value remove() {
        ScopedLock lock(mutex_);
        if (LinkedList<I>::size()) {
            return LinkedList<I>::poll();
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

 private:
    mutable Mutex mutex_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_USE_LOCKFREE

#endif  // LIBJ_DETAIL_CONCURRENT_LINKED_QUEUE_H_
