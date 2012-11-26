// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_TYPED_JS_ARRAY_H_
#define LIBJ_DETAIL_TYPED_JS_ARRAY_H_

namespace libj {

template<typename T>
typename TypedJsArray<T>::Ptr
TypedJsArray<T>::create() {
    return Ptr(new TypedJsArray());
}

template<typename T>
typename TypedJsArray<T>::Ptr
TypedJsArray<T>::create(Collection::CPtr c) {
    Ptr ary(new TypedJsArray());
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

    TypedJsArray* ary(new TypedJsArray());
    for (Size i = from; i < to; i++) {
        ary->addTyped(this->getTyped(i));
    }
    return Ptr(ary);
}

}  // namespace libj

#endif  // LIBJ_DETAIL_TYPED_JS_ARRAY_H_
