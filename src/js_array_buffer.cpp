// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/detail/js_array_buffer.h>

namespace libj {

JsArrayBuffer::Ptr JsArrayBuffer::create(Size length) {
    return Ptr(new detail::JsArrayBuffer(length));
}

}   // namespace libj
