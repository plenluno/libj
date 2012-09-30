// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_FUNCTION_H_
#define LIBJ_JS_FUNCTION_H_

#include "libj/function.h"
#include "libj/js_array.h"

namespace libj {

class JsFunction : LIBJ_FUNCTION(JsFunction)
 public:
    virtual Value operator()(JsArray::Ptr args = JsArray::null()) = 0;

    Value operator()(ArrayList::Ptr args = ArrayList::null()) {
        return operator()(JsArray::create(args));
    }
};

#define LIBJ_JS_FUNCTION(T) public libj::JsFunction { \
    LIBJ_MUTABLE_DEFS(T, libj::JsFunction) \
    String::CPtr toString() const { \
        return String::create("function " #T "() {}"); \
    }

}  // namespace libj

#endif  // LIBJ_JS_FUNCTION_H_
