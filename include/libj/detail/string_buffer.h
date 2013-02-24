// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STRING_BUFFER_H_
#define LIBJ_DETAIL_STRING_BUFFER_H_

#include <libj/typedef.h>

namespace libj {
namespace detail {

template<typename I>
class StringBuffer : public I {
 public:
    virtual Size length() const {
        return buf_.length();
    }

    virtual Char charAt(Size index) const {
        if (index >= length()) {
            return NO_CHAR;
        } else {
            return buf_[index];
        }
    }

    virtual Boolean append(const Value& val) {
        String::CPtr s = String::valueOf(val);
        if (s) {
#ifdef LIBJ_USE_UTF32
            buf_.append(s->toStdU32String());
#else
            buf_.append(s->toStdU16String());
#endif
            return true;
        } else {
            return false;
        }
    }

    virtual Boolean appendChar(Char c) {
        buf_.push_back(c);
        return true;
    }

    virtual Boolean appendCStr(const char* cstr) {
        if (!cstr) return false;

        while (Char c = static_cast<Char>(*cstr++)) {
            appendChar(c);
        }
        return true;
    }

    virtual Boolean setCharAt(Size index, Char c) {
        if (index >= length()) {
            return false;
        } else {
            buf_[index] = c;
            return true;
        }
    }

    virtual String::CPtr toString() const {
        return String::create(buf_);
    }

 private:
#ifdef LIBJ_USE_UTF32
    std::u32string buf_;
#else
    std::u16string buf_;
#endif
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_STRING_BUFFER_H_
