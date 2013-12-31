// Copyright (c) 2012 Plenluno All rights reserved.

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

}  // namespace libj
