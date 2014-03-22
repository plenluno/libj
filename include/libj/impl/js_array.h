// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_JS_ARRAY_H_
#define LIBJ_IMPL_JS_ARRAY_H_

#define LIBJ_JS_ARRAY_INSTANCEOF(ID) \
    (ID == libj::Type<libj::JsArray>::id() || LIBJ_ARRAY_LIST_INSTANCEOF(ID))

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
