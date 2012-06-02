// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_LIST_H_
#define LIBJ_LIST_H_

#include "libj/collection.h"

namespace libj {

class List : LIBJ_COLLECTION(List)
 public:
    virtual Boolean add(const Value&) = 0;
    virtual Boolean add(Size, const Value&) = 0;
    virtual Boolean set(Size, const Value&) = 0;
    virtual Value get(Size) const = 0;
    virtual Boolean remove(const Value&) = 0;
    virtual Value remove(Size) = 0;
    // and so on
};

#define LIBJ_LIST(T) public libj::List { \
    LIBJ_MUTABLE_DECLS(T, libj::List)

#define LIBJ_LIST_IMPL(L) \
public: \
    Boolean add(const Value& v) { \
        return L->add(v); \
    } \
    Boolean add(Size i, const Value& v) { \
        return L->add(i, v); \
    } \
    Boolean set(Size i, const Value& v) { \
        return L->set(i, v); \
    } \
    Value get(Size i) const { \
        return L->get(i); \
    } \
    Boolean remove(const Value& v) { \
        return L->remove(v); \
    } \
    Value remove(Size i) { \
        return L->remove(i); \
    }


}  // namespace libj

#endif  // LIBJ_LIST_H_
