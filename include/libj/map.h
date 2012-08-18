// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_MAP_H_
#define LIBJ_MAP_H_

#include "libj/set.h"

namespace libj {

class Map : LIBJ_MUTABLE(Map)
 public:
    static Ptr create();

    virtual void clear() = 0;
    virtual Boolean containsKey(const Value& key) const = 0;
    virtual Boolean containsValue(const Value& val) const = 0;
    virtual Value get(const Value& key) const = 0;
    virtual Set::CPtr keySet() const = 0;
    virtual Value put(const Value& key, const Value& val) = 0;
    virtual Value remove(const Value& key) = 0;
    virtual Size size() const = 0;
};

#define LIBJ_MAP(T) public libj::Map { \
    LIBJ_MUTABLE_DEFS(T, libj::Map)

#define LIBJ_MAP_IMPL(M) \
public: \
    void clear() { \
        M->clear(); \
    } \
    Boolean containsKey(const Value& key) const { \
        return M->containsKey(key); \
    } \
    Boolean containsValue(const Value& val) const { \
        return M->containsValue(val); \
    } \
    Value get(const Value& key) const { \
        return M->get(key); \
    } \
    Set::CPtr keySet() const { \
        return M->keySet(); \
    } \
    Value put(const Value& key, const Value& val) { \
        return M->put(key, val); \
    } \
    Value remove(const Value& key) { \
        return M->remove(key); \
    } \
    Size size() const { \
        return M->size(); \
    }

}  // namespace libj

#endif  // LIBJ_MAP_H_
