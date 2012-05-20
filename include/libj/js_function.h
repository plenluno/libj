// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_FUNCTION_H_
#define LIBJ_JS_FUNCTION_H_

#include "libj/function.h"

namespace libj {

typedef Function JsFunction;

#define LIBJ_JS_FUNCTION(T) public libj::JsFunction { \
    LIBJ_MUTABLE_DECLS(T, libj::JsFunction)

}  // namespace libj

#endif  // LIBJ_JS_FUNCTION_H_