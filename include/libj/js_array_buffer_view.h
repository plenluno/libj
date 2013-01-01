// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_JS_ARRAY_BUFFER_VIEW_H_
#define LIBJ_JS_ARRAY_BUFFER_VIEW_H_

#include <libj/js_array_buffer.h>

namespace libj {

class JsArrayBufferView : LIBJ_MUTABLE(JsArrayBufferView)
 public:
    virtual JsArrayBuffer::Ptr buffer() const = 0; 

    virtual Size byteOffset() const = 0;

    virtual Size byteLength() const = 0;
};

}  // namespace libj

#define LIBJ_JS_ARRAY_BUFFER_VIEW(T) public libj::JsArrayBufferView { \
    LIBJ_MUTABLE_DEFS(T, libj::JsArrayBufferView)

#endif  // LIBJ_JS_ARRAY_BUFFER_VIEW_H_
