// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_MAP_H_
#define LIBJ_MAP_H_

#include "libj/mutable.h"
#include "libj/set.h"

namespace libj {

class Map : LIBJ_MUTABLE(Map)
 public:
    virtual Size size() const = 0;
    virtual Value get(const Value& key) const = 0;
    virtual Value put(const Value& key, const Value& val) = 0;
    virtual Value remove(const Value& key) = 0;
    virtual Set::CPtr keySet() const = 0;
    virtual void clear() = 0;
    // and so on
};

#define LIBJ_MAP(T) public libj::Map { \
    LIBJ_MUTABLE_DECLS(T, libj::Map)

#define LIBJ_MAP_IMPL(M) \
 public: \
    Size size() const { \
        return M->size(); \
    } \
    Value get(const Value& key) const { \
        return M->get(key); \
    } \
    Value put(const Value& key, const Value& val) { \
        return M->put(key, val); \
    } \
    Value remove(const Value& key) { \
        return M->remove(key); \
    } \
    Set::CPtr keySet() const { \
        return M->keySet(); \
    } \
    void clear() { \
        M->clear(); \
    }

}  // namespace libj

#endif  // LIBJ_MAP_H_