// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_JS_OBJECT_H_
#define LIBJ_IMPL_JS_OBJECT_H_

#define LIBJ_JS_OBJECT_INSTANCEOF(ID) \
    (ID == libj::Type<libj::JsObject>::id() || LIBJ_MAP_INSTANCEOF(ID))

namespace libj {

template<typename T>
inline typename Type<T>::Ptr JsObject::getPtr(const Value& name) const {
    return toPtr<T>(get(name));
}

template<typename T>
inline typename Type<T>::Ptr JsObject::getPtr(String::CPtr name) const {
    return toPtr<T>(get(name));
}

template<typename T>
inline typename Type<T>::CPtr JsObject::getCPtr(const Value& name) const {
    return toCPtr<T>(get(name));
}

template<typename T>
inline typename Type<T>::CPtr JsObject::getCPtr(String::CPtr name) const {
    return toCPtr<T>(get(name));
}

}  // namespace libj

#endif  // LIBJ_IMPL_JS_OBJECT_H_
