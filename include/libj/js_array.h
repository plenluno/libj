// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_H_
#define LIBJ_JS_ARRAY_H_

#include "libj/array_list.h"

namespace libj {

typedef ArrayList JsArray;

#define LIBJ_JS_ARRAY(T) public libj::JsArray { \
    LIBJ_MUTABLE_DECLS(T, libj::JsArray)

}  // namespace libj

#endif  // LIBJ_JS_ARRAY_H_