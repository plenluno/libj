// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_LIST_H_
#define LIBJ_LIST_H_

#include <libj/collection.h>

namespace libj {

class List : LIBJ_COLLECTION(List)
 public:
    virtual Boolean add(const Value& val) = 0;

    virtual Boolean add(Size index, const Value& val) = 0;

    virtual Value get(Size index) const = 0;

    virtual Int indexOf(const Value& val) = 0;

    virtual Int lastIndexOf(const Value& val) = 0;

    virtual Value remove(Size index) = 0;

    virtual Boolean remove(const Value& val) = 0;

    virtual Iterator::Ptr reverseIterator() const = 0;

    virtual Boolean set(Size index, const Value& val) = 0;

    virtual Value subList(Size from, Size to) const = 0;

 public:
    virtual Size length() const = 0;

    virtual Value shift() = 0;

    virtual Size unshift(const Value& val) = 0;

    virtual Size push(const Value& val) = 0;

    virtual Value pop() = 0;
};

#define LIBJ_LIST(T) public libj::List { \
    LIBJ_MUTABLE_DEFS(T, libj::List)

}  // namespace libj

#endif  // LIBJ_LIST_H_
