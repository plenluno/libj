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
    static Ptr create(Iterator::Ptr i) {
        return Ptr(new TypedIterator(i));
    }

    Boolean hasNext() const {
        return itr_->hasNext();
    }

    Value next() {
        return itr_->next();
    }

    T nextTyped() {
        Value v = next();
        T t;
        if (to<T>(v, &t)) {
            return t;
        } else {
            LIBJ_THROW(Error::ILLEGAL_TYPE);
        }
    }

    String::CPtr toString() const {
        return itr_->toString();
    }

 private:
    Iterator::Ptr itr_;

    TypedIterator(Iterator::Ptr i) : itr_(i) {}
};

}  // namespace libj

#endif  // LIBJ_USE_EXCEPTION

#endif  // LIBJ_TYPED_ITERATOR_H_
