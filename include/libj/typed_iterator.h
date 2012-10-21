// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ITERATOR_H_
#define LIBJ_TYPED_ITERATOR_H_

#include "libj/mutable.h"

namespace libj {

template<typename T>
class TypedIterator : LIBJ_MUTABLE_TEMPLATE(TypedIterator<T>)
 public:
    virtual Boolean hasNext() const = 0;
    virtual T next() = 0;
};

}  // namespace libj

#endif  // LIBJ_TYPED_ITERATOR_H_
