// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_VALUE_HOLDER_H_
#define LIBJ_IMPL_TYPED_VALUE_HOLDER_H_

#include <libj/detail/generic_value_holder.h>

namespace libj {

template<typename T>
typename TypedValueHolder<T>::Ptr
TypedValueHolder<T>::create(const T& val) {
    typedef TypedValueHolder<T> I;
    TypedValueHolder* holder = new detail::GenericValueHolder<I, T>();
    holder->set(val);
    return Ptr(holder);
}

template<typename T>
T TypedValueHolder<T>::getTyped() const {
    typedef TypedValueHolder<T> I;
    const detail::GenericValueHolder<I, T>* holder =
        static_cast<const detail::GenericValueHolder<I, T>*>(this);
    return holder->getTyped();
}

template<typename T>
void TypedValueHolder<T>::setTyped(const T& t) {
    typedef TypedValueHolder<T> I;
    detail::GenericValueHolder<I, T>* holder =
        static_cast<detail::GenericValueHolder<I, T>*>(this);
    holder->setTyped(t);
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_VALUE_HOLDER_H_
