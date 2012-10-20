// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ITERATOR_H_
#define LIBJ_TYPED_ITERATOR_H_

#ifdef LIBJ_USE_EXCEPTION

#include "libj/iterator.h"
#include "libj/string.h"

namespace libj {

template<typename T>
class TypedIterator : LIBJ_ITERATOR_TEMPLATE(TypedIterator<T>)
 public:
    virtual T nextTyped() = 0;
};

}  // namespace libj

#endif  // LIBJ_USE_EXCEPTION

#endif  // LIBJ_TYPED_ITERATOR_H_
