// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_TYPED_VALUE_HOLDER_H_
#define LIBJ_DETAIL_TYPED_VALUE_HOLDER_H_

namespace libj {

template<typename T>
typename TypedValueHolder<T>::Ptr
TypedValueHolder<T>::create(const T& val) {
    TypedValueHolder* holder = new TypedValueHolder();
    holder->set(val);
    return Ptr(holder);
}

}  // namespace libj

#endif  // LIBJ_DETAIL_TYPED_VALUE_HOLDER_H_
