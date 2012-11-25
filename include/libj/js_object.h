// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_OBJECT_H_
#define LIBJ_JS_OBJECT_H_

#include "libj/map.h"

namespace libj {

class JsObject : LIBJ_MAP(JsObject)
 public:
    static Ptr create();

    virtual Boolean hasProperty(const Value& name) const = 0;

    virtual Value getProperty(const Value& name) const = 0;

    virtual Value setProperty(const Value& name, const Value& val) = 0;

    virtual Value deleteProperty(const Value& name) = 0;

 public:
    template<typename T>
    typename Type<T>::Ptr getPtr(const Value& name) const {
        return toPtr<T>(get(name));
    }

    template<typename T>
    typename Type<T>::CPtr getCPtr(const Value& name) const {
        return toCPtr<T>(get(name));
    }
};

#define LIBJ_JS_OBJECT(T) public libj::JsObject { \
    LIBJ_MUTABLE_DEFS(T, libj::JsObject)

}  // namespace libj

#endif  // LIBJ_JS_OBJECT_H_
