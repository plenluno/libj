// Copyright (c) 2013-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_SET_H_
#define LIBJ_IMPL_TYPED_SET_H_

#include <libj/detail/generic_set.h>

namespace libj {

template<typename T>
typename TypedSet<T>::Ptr
TypedSet<T>::create() {
    typedef TypedSet<T> I;
    return Ptr(new detail::GenericSet<I, T>());
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_SET_H_
