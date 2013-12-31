// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_OBJECT_H_
#define LIBJ_DETAIL_JS_OBJECT_H_

#include <libj/symbol.h>
#include <libj/detail/map.h>

namespace libj {
namespace detail {

template<typename I>
class JsObject : public Map<I> {
 public:
    virtual Boolean containsKey(const Value& key) const {
        return Map<I>::containsKey(String::valueOf(key));
    }

    virtual Boolean containsKey(String::CPtr key) const {
        return Map<I>::containsKey(key);
    }

    virtual Value get(const Value& key) const {
        return Map<I>::get(String::valueOf(key));
    }

    virtual Value get(String::CPtr key) const {
        return Map<I>::get(key);
    }

    virtual Value put(const Value& key, const Value& val) {
        return Map<I>::put(String::valueOf(key), val);
    }

    virtual Value put(String::CPtr key, const Value& val) {
        return Map<I>::put(key, val);
    }

    virtual Value remove(const Value& key) {
        return Map<I>::remove(String::valueOf(key));
    }

    virtual Value remove(String::CPtr key) {
        return Map<I>::remove(key);
    }

    virtual String::CPtr toString() const {
        LIBJ_STATIC_SYMBOL_DEF(symObject, "[object Object]");
        return symObject;
    }

 public:
    virtual Boolean hasProperty(const Value& name) const {
        return containsKey(name);
    }

    virtual Boolean hasProperty(String::CPtr name) const {
        return containsKey(name);
    }

    virtual Value getProperty(const Value& name) const {
        return get(name);
    }

    virtual Value getProperty(String::CPtr name) const {
        return get(name);
    }

    virtual Value setProperty(const Value& name, const Value& val) {
        return put(name, val);
    }

    virtual Value setProperty(String::CPtr name, const Value& val) {
        return put(name, val);
    }

    virtual Value deleteProperty(const Value& name) {
        return remove(name);
    }

    virtual Value deleteProperty(String::CPtr name) {
        return remove(name);
    }
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_OBJECT_H_
