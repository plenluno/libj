// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_TYPED_JS_ARRAY_H_
#define LIBJ_IMPL_TYPED_JS_ARRAY_H_

#include <libj/detail/generic_js_array.h>

namespace libj {

template<typename T>
typename TypedJsArray<T>::Ptr
TypedJsArray<T>::create() {
    typedef TypedJsArray<T> I;
    return Ptr(new detail::GenericJsArray<I, T>());
}

template<typename T>
typename TypedJsArray<T>::Ptr
TypedJsArray<T>::create(Collection::CPtr c) {
    typedef TypedJsArray<T> I;
    Ptr ary(new detail::GenericJsArray<I, T>());
    Iterator::Ptr itr = c->iterator();
    while (itr->hasNext()) {
        Value v = itr->next();
        T t;
        if (detail::convert<T>(v, &t)) {
            ary->addTyped(t);
        } else {
            return null();
        }
    }
    return ary;
}

template<typename T>
Value TypedJsArray<T>::subList(Size from, Size to) const {
    if (to > this->size() || from > to) {
        LIBJ_HANDLE_ERROR(Error::INDEX_OUT_OF_BOUNDS);
    }

    typedef TypedJsArray<T> I;
    TypedJsArray* ary(new detail::GenericJsArray<I, T>());
    for (Size i = from; i < to; i++) {
        ary->addTyped(this->getTyped(i));
    }
    return Ptr(ary);
}

}  // namespace libj

#endif  // LIBJ_IMPL_TYPED_JS_ARRAY_H_
