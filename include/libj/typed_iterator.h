// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ITERATOR_H_
#define LIBJ_TYPED_ITERATOR_H_

#include <libj/iterator.h>
#include <libj/typed_mutable.h>

namespace libj {

template<typename T>
class TypedIterator : LIBJ_TYPED_MUTABLE_IF(Iterator, T)
 public:
    virtual T nextTyped() = 0;
};

}  // namespace libj

#endif  // LIBJ_TYPED_ITERATOR_H_
