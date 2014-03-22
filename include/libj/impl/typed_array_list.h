// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_ARRAY_LIST_H_
#define LIBJ_IMPL_TYPED_ARRAY_LIST_H_

#include <libj/detail/generic_array_list.h>

namespace libj {

template<typename T>
typename TypedArrayList<T>::Ptr
TypedArrayList<T>::create() {
    typedef TypedArrayList<T> I;
    return Ptr(new detail::GenericArrayList<I, T>());
}

template<typename T>
typename TypedArrayList<T>::Ptr
TypedArrayList<T>::create(Collection::CPtr c) {
    typedef TypedArrayList<T> I;
    Ptr list(new detail::GenericArrayList<I, T>());
    Iterator::Ptr itr = c->iterator();
    while (itr->hasNext()) {
        Value v = itr->next();
        T t;
        if (detail::convert<T>(v, &t)) {
            list->addTyped(t);
        } else {
            return null();
        }
    }
    return list;
}

template<typename T>
Value TypedArrayList<T>::subList(Size from, Size to) const {
    if (to > this->size() || from > to) {
        LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
    }

    typedef TypedArrayList<T> I;
    TypedArrayList* list(new detail::GenericArrayList<I, T>());
    for (Size i = from; i < to; i++) {
        list->addTyped(this->getTyped(i));
    }
    return Ptr(list);
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_ARRAY_LIST_H_
