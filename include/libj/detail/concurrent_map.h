// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_CONCURRENT_MAP_H_
#define LIBJ_DETAIL_CONCURRENT_MAP_H_

#include <libj/detail/map.h>
#include <libj/detail/scoped_lock.h>

namespace libj {
namespace detail {

template<typename I>
class ConcurrentMap : public Map<I> {
 public:
    virtual Size size() const {
        ScopedLock lock(mutex_);
        return Map<I>::size();
    }

    virtual Boolean containsKey(const Value& key) const {
        ScopedLock lock(mutex_);
        return Map<I>::containsKey(key);
    }

    virtual Boolean containsValue(const Value& val) const {
        ScopedLock lock(mutex_);
        return Map<I>::containsValue(val);
    }

    virtual Value get(const Value& key) const {
        ScopedLock lock(mutex_);
        return Map<I>::get(key);
    }

    virtual Value put(const Value& key, const Value& val) {
        ScopedLock lock(mutex_);
        return Map<I>::put(key, val);
    }

    virtual Value remove(const Value& key) {
        ScopedLock lock(mutex_);
        return Map<I>::remove(key);
    }

    virtual Set::CPtr keySet() const {
        ScopedLock lock(mutex_);
        return Map<I>::keySet();
    }

    virtual void clear() {
        ScopedLock lock(mutex_);
        Map<I>::clear();
    }

    virtual Boolean isEmpty() const {
        ScopedLock lock(mutex_);
        return Map<I>::isEmpty();
    }

    virtual String::CPtr toString() const {
        ScopedLock lock(mutex_);
        return Map<I>::toString();
    }

 private:
    mutable Mutex mutex_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_CONCURRENT_MAP_H_
