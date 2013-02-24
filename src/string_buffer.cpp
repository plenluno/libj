// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/detail/string_buffer.h>

namespace libj {

StringBuffer::Ptr StringBuffer::create() {
    return Ptr(new detail::StringBuffer());
}

}  // namespace libj
