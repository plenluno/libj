// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_H_
#define LIBJ_JS_ARRAY_H_

#include "libj/array_list.h"
#include "libj/js_property.h"

namespace libj {

class JsArray
    : public JsPropertyMixin
    , LIBJ_ARRAY_LIST(JsArray)
 public:
    static Ptr create();
    static Ptr create(ArrayList::CPtr);

 public:
    template<typename T>
    typename Type<T>::Ptr getPtr(Size index) const {
        return toPtr<T>(get(index));
    }

    template<typename T>
    typename Type<T>::CPtr getCPtr(Size index) const {
        return toCPtr<T>(get(index));
    }
};

#define LIBJ_JS_ARRAY(T) public libj::JsArray { \
    LIBJ_MUTABLE_DEFS(T, libj::JsArray)

}  // namespace libj

#endif  // LIBJ_JS_ARRAY_H_
