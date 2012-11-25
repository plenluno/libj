// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_OBJECT_H_
#define LIBJ_DETAIL_JS_OBJECT_H_

#include "libj/symbol.h"

#include "./map.h"

namespace libj {
namespace detail {

template<typename I>
class JsObject : public Map<I> {
 public:
    virtual Boolean containsKey(const Value& key) const {
        return Map<I>::containsKey(String::valueOf(key));
    }

    virtual Value get(const Value& key) const {
        return Map<I>::get(String::valueOf(key));
    }

    virtual Value put(const Value& key, const Value& val) {
        return Map<I>::put(String::valueOf(key), val);
    }

    virtual Value remove(const Value& key) {
        return Map<I>::remove(String::valueOf(key));
    }

    virtual String::CPtr toString() const {
        LIBJ_STATIC_SYMBOL_DEF(symObject, "[object Object]");
        return symObject;
    }

 public:
    virtual Boolean hasProperty(const Value& name) const {
        return containsKey(name);
    }

    virtual Value getProperty(const Value& name) const {
        return get(name);
    }

    virtual Value setProperty(const Value& name, const Value& val) {
        return put(name, val);
    }

    virtual Value deleteProperty(const Value& name) {
        return remove(name);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_OBJECT_H_
