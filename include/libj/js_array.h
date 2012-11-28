// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_H_
#define LIBJ_JS_ARRAY_H_

#include <libj/array_list.h>

namespace libj {

class JsArray : LIBJ_ARRAY_LIST(JsArray)
 public:
    static Ptr create();

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
    LIBJ_MUTABLE_DEFS(T, libj::JsArray)

#endif  // LIBJ_JS_ARRAY_H_
