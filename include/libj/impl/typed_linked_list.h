// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_LINKED_LIST_H_
#define LIBJ_IMPL_TYPED_LINKED_LIST_H_

#include <libj/detail/generic_linked_list.h>

namespace libj {

template<typename T>
typename TypedLinkedList<T>::Ptr
TypedLinkedList<T>::create() {
    typedef TypedLinkedList<T> I;
    return Ptr(new detail::GenericLinkedList<I, T>());
}

template<typename T>
typename TypedLinkedList<T>::Ptr
TypedLinkedList<T>::create(Collection::CPtr c) {
    typedef TypedLinkedList<T> I;
    Ptr list(new detail::GenericLinkedList<I, T>());
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
Value TypedLinkedList<T>::subList(Size from, Size to) const {
    if (to > this->size() || from > to) {
        LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
    }

    typedef TypedLinkedList<T> I;
    TypedLinkedList* list(new detail::GenericLinkedList<I, T>());
    for (Size i = from; i < to; i++) {
        list->addTyped(this->getTyped(i));
    }
    return Ptr(list);
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_LINKED_LIST_H_
