// Copyright (c) 2014 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_JS_ARRAY_BUFFER_VIEW_H_
#define LIBJ_IMPL_JS_ARRAY_BUFFER_VIEW_H_

#define LIBJ_JS_ARRAY_BUFFER_VIEW_INSTANCEOF(ID) \
    (ID == libj::Type<libj::JsArrayBufferView>::id() \
        || LIBJ_MUTABLE_INSTANCEOF(ID))

#endif  // LIBJ_IMPL_JS_ARRAY_BUFFER_VIEW_H_
