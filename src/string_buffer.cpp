// Copyright (c) 2012 Plenluno All rights reserved.

#include <list>

#include "libj/string_buffer.h"

namespace libj {

class StringBufferImpl : public StringBuffer {
 public:
    static Ptr create() {
        return Ptr(new StringBufferImpl());
    }

    Size length() const {
        return buf_.length();
    }

    Char charAt(Size index) const {
        if (index >= length()) {
            return NO_CHAR;
        } else {
            return buf_[index];
        }
    }

    Boolean append(const Value& val) {
        String::CPtr s = String::valueOf(val);
        if (s) {
            buf_.append(s->toStdU32String());
            return true;
        } else {
            return false;
        }
    }

    Boolean appendChar(Char c) {
        buf_.push_back(c);
        return true;
    }

    Boolean appendCStr(const char* cstr) {
        if (!cstr) return false;

        while (Char c = static_cast<Char>(*cstr++)) {
            appendChar(c);
        }
        return true;
    }

    Boolean setCharAt(Size index, Char c) {
        if (index >= length()) {
            return false;
        } else {
            buf_[index] = c;
            return true;
        }
    }

    String::CPtr toString() const {
        return String::create(buf_);
    }

 private:
    std::u32string buf_;
};

StringBuffer::Ptr StringBuffer::create() {
    return StringBufferImpl::create();
}

}  // namespace libj
