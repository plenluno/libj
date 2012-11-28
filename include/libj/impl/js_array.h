// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_JS_ARRAY_H_
#define LIBJ_IMPL_JS_ARRAY_H_

namespace libj {

template<typename T>
typename Type<T>::Ptr JsArray::getPtr(Size index) const {
    return toPtr<T>(get(index));
}

template<typename T>
typename Type<T>::CPtr JsArray::getCPtr(Size index) const {
    return toCPtr<T>(get(index));
}

}  // namespace libj

#endif  // LIBJ_IMPL_JS_ARRAY_H_
