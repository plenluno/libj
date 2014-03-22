// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_ITERATOR_H_
#define LIBJ_ITERATOR_H_

#include <libj/mutable.h>
#include <libj/value.h>

namespace libj {

class Iterator : LIBJ_MUTABLE(Iterator)
 public:
    virtual Boolean hasNext() const = 0;

    virtual Value next() = 0;
};

}  // namespace libj

#include <libj/impl/iterator.h>

#define LIBJ_ITERATOR_TEMPLATE(T) public libj::Iterator { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_ITERATOR)

#endif  // LIBJ_ITERATOR_H_
