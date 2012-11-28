// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_FUNCTION_H_
#define LIBJ_JS_FUNCTION_H_

#include <libj/function.h>
#include <libj/js_array.h>

namespace libj {

class JsFunction : LIBJ_FUNCTION(JsFunction)
 public:
    virtual Value operator()(JsArray::Ptr args = JsArray::null()) = 0;

    virtual Value operator()(ArrayList::Ptr args);

    virtual Value call();

    virtual Value call(const Value& v1);

    virtual Value call(const Value& v1, const Value& v2);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6,
                       const Value& v7);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6,
                       const Value& v7, const Value& v8);

    virtual Value call(const Value& v1, const Value& v2, const Value& v3,
                       const Value& v4, const Value& v5, const Value& v6,
                       const Value& v7, const Value& v8, const Value& v9);
};

}  // namespace libj

#include <libj/impl/js_function.h>

#define LIBJ_JS_FUNCTION(T) public libj::JsFunction { \
    LIBJ_JS_FUNCTION_DEFS(T)

#endif  // LIBJ_JS_FUNCTION_H_
