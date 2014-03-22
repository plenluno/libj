// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_COLLECTION_H_
#define LIBJ_TYPED_COLLECTION_H_

#include <libj/typed_mutable.h>
#include <libj/typed_iterator.h>

namespace libj {

template<typename T>
class TypedCollection : public TypedMutable<T> {
 public:
    virtual Boolean addTyped(const T& t) = 0;

    virtual Boolean removeTyped(const T& t) = 0;

    virtual typename TypedIterator<T>::Ptr iteratorTyped() const = 0;
};

}  // namespace libj

#endif  // LIBJ_TYPED_COLLECTION_H_
