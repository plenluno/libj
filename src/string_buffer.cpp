// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/detail/string_buffer.h>

namespace libj {

StringBuffer::Ptr StringBuffer::create() {
    return Ptr(new detail::StringBuffer());
}

StringBuffer::Ptr StringBuffer::create(Size capacity) {
    detail::StringBuffer* s = new detail::StringBuffer();
    s->ensureCapacity(capacity);
    return Ptr(s);
}

StringBuffer::Ptr StringBuffer::create(String::CPtr str) {
    if (str) {
        return Ptr(new detail::StringBuffer(str));
    } else {
        return StringBuffer::null();
    }
}

}  // namespace libj
