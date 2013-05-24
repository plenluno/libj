// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_SET_H_
#define LIBJ_IMPL_TYPED_SET_H_

namespace libj {

template<typename T>
typename TypedSet<T>::Ptr
TypedSet<T>::create() {
    return Ptr(new TypedSet());
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_SET_H_
