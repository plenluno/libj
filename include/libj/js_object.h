// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_JS_OBJECT_H_
#define LIBJ_JS_OBJECT_H_

#include <libj/map.h>

namespace libj {

class JsObject : LIBJ_MAP(JsObject)
 public:
    static Ptr create();

    virtual Value get(const Value& key) const = 0;

    virtual Value get(String::CPtr key) const = 0;

    virtual Value put(const Value& key, const Value& val) = 0;

    virtual Value put(String::CPtr key, const Value& val) = 0;

 public:
    virtual Boolean hasProperty(const Value& name) const = 0;

    virtual Value getProperty(const Value& name) const = 0;

    virtual Value setProperty(const Value& name, const Value& val) = 0;

    virtual Value deleteProperty(const Value& name) = 0;

    template<typename T>
    typename Type<T>::Ptr getPtr(const Value& name) const;

    template<typename T>
    typename Type<T>::CPtr getCPtr(const Value& name) const;
};

}  // namespace libj

#include <libj/impl/js_object.h>

#define LIBJ_JS_OBJECT(T) public libj::JsObject { \
    LIBJ_MUTABLE_DEFS(T, libj::JsObject)

#endif  // LIBJ_JS_OBJECT_H_
