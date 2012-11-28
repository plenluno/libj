// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/js_array_buffer.h>
#include <libj/detail/js_array_buffer.h>

namespace libj {

JsArrayBuffer::Ptr JsArrayBuffer::create(Size length) {
    return Ptr(new detail::JsArrayBuffer<JsArrayBuffer>(length));
}

}   // namespace libj
