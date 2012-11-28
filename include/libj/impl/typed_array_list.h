// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_ARRAY_LIST_H_
#define LIBJ_IMPL_TYPED_ARRAY_LIST_H_

namespace libj {

template<typename T>
typename TypedArrayList<T>::Ptr
TypedArrayList<T>::create() {
    return Ptr(new TypedArrayList());
}

template<typename T>
typename TypedArrayList<T>::Ptr
TypedArrayList<T>::create(Collection::CPtr c) {
    Ptr list(new TypedArrayList());
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

    TypedArrayList* list(new TypedArrayList());
    for (Size i = from; i < to; i++) {
        list->addTyped(this->getTyped(i));
    }
    return Ptr(list);
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_ARRAY_LIST_H_
