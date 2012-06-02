// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_OBJECT_H_
#define LIBJ_JS_OBJECT_H_

#include "libj/map.h"
#include "libj/string.h"

namespace libj {

class JsObject : LIBJ_MAP(JsObject)
 public:
    static Ptr create();

    template<typename T>
    typename Type<T>::Ptr getPtr(String::CPtr name) const {
        Value v = get(name);
        typename Type<T>::Ptr p = toPtr<T>(v);
        return p;
    }

    template<typename T>
    typename Type<T>::CPtr getCPtr(String::CPtr name) const {
        Value v = get(name);
        typename Type<T>::CPtr p = toCPtr<T>(v);
        return p;
    }
};

#define LIBJ_JS_OBJECT(T) public libj::JsObject { \
    LIBJ_MUTABLE_DECLS(T, libj::JsObject)

#define LIBJ_JS_OBJECT_IMPL(JO) \
    LIBJ_MAP_IMPL(JO) \
public: \
    String::CPtr toString() const { \
        return JO->toString(); \
    }

}  // namespace libj

#endif  // LIBJ_JS_OBJECT_H_
