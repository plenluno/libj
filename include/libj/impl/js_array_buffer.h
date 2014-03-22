// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_JS_ARRAY_BUFFER_H_
#define LIBJ_IMPL_JS_ARRAY_BUFFER_H_

#define LIBJ_JS_ARRAY_BUFFER_INSTANCEOF(ID) \
    (ID == libj::Type<libj::JsArrayBuffer>::id() || LIBJ_MUTABLE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_JS_ARRAY_BUFFER_H_
