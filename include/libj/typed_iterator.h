// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_TYPED_ITERATOR_H_
#define LIBJ_TYPED_ITERATOR_H_

#include <libj/iterator.h>

namespace libj {

template<typename T>
class TypedIterator : LIBJ_ITERATOR_TEMPLATE(TypedIterator)
 public:
    virtual T nextTyped() = 0;
};

}  // namespace libj

#endif  // LIBJ_TYPED_ITERATOR_H_
