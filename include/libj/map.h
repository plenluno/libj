// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_MAP_H_
#define LIBJ_MAP_H_

#include "libj/mutable.h"
#include "libj/set.h"

namespace libj {

class Map : LIBJ_MUTABLE(Map)
 public:
    virtual Size size() const = 0;
    virtual Value get(Value key) const = 0;
    virtual Value put(Value key, Value val) = 0;
    virtual Value remove(Value key) = 0;
    virtual Type<Set>::Cptr keySet() const = 0;
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
    Value get(Value key) const { \
        return M->get(key); \
    } \
    Value put(Value key, Value val) { \
        return M->put(key, val); \
    } \
    Value remove(Value key) { \
        return M->remove(key); \
    } \
    Type<Set>::Cptr keySet() const { \
        return M->keySet(); \
    } \
    void clear() { \
        M->clear(); \
    }

}  // namespace libj

#endif  // LIBJ_MAP_H_