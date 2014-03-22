// Copyright (c) 2012-2014 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_H_
#define LIBJ_JS_ARRAY_H_

#include <libj/array_list.h>

namespace libj {

class JsArray : LIBJ_ARRAY_LIST(JsArray)
 public:
    static Ptr create(Size length = 0);

    static Ptr create(ArrayList::CPtr);

    virtual Boolean hasProperty(const Value& name) const = 0;

    virtual Value getProperty(const Value& name) const = 0;

    virtual Value setProperty(const Value& name, const Value& val) = 0;

    virtual Value deleteProperty(const Value& name) = 0;

    template<typename T>
    typename Type<T>::Ptr getPtr(Size index) const;

    template<typename T>
    typename Type<T>::CPtr getCPtr(Size index) const;
};

}  // namespace libj

#include <libj/impl/js_array.h>

#define LIBJ_JS_ARRAY(T) public libj::JsArray { \
    LIBJ_MUTABLE_DEFS(T, LIBJ_JS_ARRAY)

#define LIBJ_JS_ARRAY_TEMPLATE(T) public libj::JsArray { \
    LIBJ_MUTABLE_TEMPLATE_DEFS(T, LIBJ_JS_ARRAY)

#endif  // LIBJ_JS_ARRAY_H_
