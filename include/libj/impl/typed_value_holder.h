// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_VALUE_HOLDER_H_
#define LIBJ_IMPL_TYPED_VALUE_HOLDER_H_

namespace libj {

template<typename T>
typename TypedValueHolder<T>::Ptr
TypedValueHolder<T>::create(const T& val) {
    TypedValueHolder* holder = new TypedValueHolder();
    holder->set(val);
    return Ptr(holder);
}

template<typename T>
T TypedValueHolder<T>::getTyped() const {
    typedef TypedMutable<ValueHolder, T> I;
    return detail::GenericValueHolder<I, T>::getTyped();
}

template<typename T>
void TypedValueHolder<T>::setTyped(const T& t) {
    typedef TypedMutable<ValueHolder, T> I;
    detail::GenericValueHolder<I, T>::setTyped(t);
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_VALUE_HOLDER_H_
