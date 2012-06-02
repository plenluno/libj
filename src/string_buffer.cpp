// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/string_buffer.h"

namespace libj {

class StringBufferImpl : public StringBuffer {
 public:
    static Ptr create() {
        Ptr p(new StringBufferImpl());
        return p;
    }

    Size length() const {
        return str_->length();
    }

    Char charAt(Size n) const {
        return str_->charAt(n);
    }

    // TODO(plenluno): make it more efficient
    Boolean append(const Value& val) {
        String::CPtr s = String::valueOf(val);
        if (s) {
            str_ = str_->concat(s);
            return true;
        } else {
            return false;
        }
    }

    String::CPtr toString() const {
        return str_->toString();
    }

 private:
    StringBufferImpl() : str_(String::create()) {}

    String::CPtr str_;
};

StringBuffer::Ptr StringBuffer::create() {
    return StringBufferImpl::create();
}

}  // namespace libj
