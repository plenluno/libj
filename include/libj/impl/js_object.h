// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_JS_OBJECT_H_
#define LIBJ_IMPL_JS_OBJECT_H_

namespace libj {

template<typename T>
inline typename Type<T>::Ptr JsObject::getPtr(const Value& name) const {
    return toPtr<T>(get(name));
}

template<typename T>
inline typename Type<T>::CPtr JsObject::getCPtr(const Value& name) const {
    return toCPtr<T>(get(name));
}

}  // namespace libj

#endif  // LIBJ_IMPL_JS_OBJECT_H_
