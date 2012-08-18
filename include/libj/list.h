// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_LIST_H_
#define LIBJ_LIST_H_

#include "libj/collection.h"

namespace libj {

class List : LIBJ_COLLECTION(List)
 public:
    virtual Boolean add(const Value&) = 0;
    virtual Boolean add(Size, const Value&) = 0;
    // TODO(plenluno): implement
    // virtual Boolean addAll(Collection::CPtr) = 0;
    // virtual Boolean addAll(Size, Collection::CPtr) = 0;
    virtual Value get(Size) const = 0;
    virtual Value remove(Size) = 0;
    virtual Boolean remove(const Value&) = 0;
    virtual Boolean set(Size, const Value&) = 0;
    // virtual Ptr subList(Size from) = 0;
    // virtual Ptr subList(Size from, Size to) = 0;

    Size length() const {
        return size();
    }
};

#define LIBJ_LIST(T) public libj::List { \
    LIBJ_MUTABLE_DEFS(T, libj::List)

#define LIBJ_LIST_IMPL(L) \
    LIBJ_COLLECTION_IMPL(L) \
public: \
    Boolean add(Size i, const Value& v) { \
        return L->add(i, v); \
    } \
    Boolean set(Size i, const Value& v) { \
        return L->set(i, v); \
    } \
    Value get(Size i) const { \
        return L->get(i); \
    } \
    Value remove(Size i) { \
        return L->remove(i); \
    }

}  // namespace libj

#endif  // LIBJ_LIST_H_
