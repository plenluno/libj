// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_COLLECTION_H_
#define LIBJ_COLLECTION_H_

#include <libj/iterator.h>
#include <libj/string.h>

namespace libj {

class Collection : LIBJ_MUTABLE(Collection)
 public:
    virtual Boolean add(const Value& val) = 0;

    virtual Boolean addAll(CPtr collection) = 0;

    virtual void clear() = 0;

    virtual Boolean contains(const Value& val) const = 0;

    virtual Boolean containsAll(CPtr collection) const = 0;

    virtual Boolean isEmpty() const = 0;

    virtual Iterator::Ptr iterator() const = 0;

    virtual Boolean remove(const Value& val) = 0;

    virtual Boolean removeAll(CPtr collection) = 0;

    virtual Boolean retainAll(CPtr collection) = 0;

    virtual Size size() const = 0;
};

}  // namespace libj

#include <libj/impl/collection.h>

#define LIBJ_COLLECTION(T) public libj::Collection { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_COLLECTION)

#endif  // LIBJ_COLLECTION_H_
