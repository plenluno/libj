// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_H_
#define LIBJ_JS_ARRAY_H_

#include "libj/array_list.h"

namespace libj {

class JsArray : LIBJ_ARRAY_LIST(JsArray)
 public:
    static Ptr create();
    static Ptr create(ArrayList::CPtr);

    Boolean hasProperty(const Value& name) const;
    Value getProperty(const Value& name) const;
    void setProperty(const Value& name, const Value& val);
    void deleteProperty(const Value& name);

    template<typename T>
    typename Type<T>::Ptr getPtr(Size index) const {
        Value v = get(index);
        typename Type<T>::Ptr p = toPtr<T>(v);
        return p;
    }

    template<typename T>
    typename Type<T>::CPtr getCPtr(Size index) const {
        Value v = get(index);
        typename Type<T>::CPtr p = toCPtr<T>(v);
        return p;
    }
};

#define LIBJ_JS_ARRAY(T) public libj::JsArray { \
    LIBJ_MUTABLE_DEFS(T, libj::JsArray)

}  // namespace libj

#endif  // LIBJ_JS_ARRAY_H_
