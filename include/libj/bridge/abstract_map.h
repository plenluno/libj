// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_MAP_H_
#define LIBJ_BRIDGE_ABSTRACT_MAP_H_

#include "libj/map.h"

namespace libj {
namespace bridge {

template<typename T>
class AbstractMap : public T {
 public:
    AbstractMap(Map::Ptr map) : map_(map) {}

    virtual void clear() {
        map_->clear();
    }

    virtual Boolean containsKey(const Value& key) const {
        return map_->containsKey(key);
    }

    virtual Boolean containsValue(const Value& val) const {
        return map_->containsValue(val);
    }

    virtual Value get(const Value& key) const {
        return map_->get(key);
    }

    virtual Boolean isEmpty() const {
        return map_->isEmpty();
    }

    virtual Set::CPtr keySet() const {
        return map_->keySet();
    }

    virtual Value put(const Value& key, const Value& val) {
        return map_->put(key, val);
    }

    virtual Value remove(const Value& key) {
        return map_->remove(key);
    }

    virtual Size size() const {
        return map_->size();
    }

 private:
    Map::Ptr map_;
};

}  // namespace bridge
}  // namespace libj

#endif  // LIBJ_BRIDGE_ABSTRACT_MAP_H_
