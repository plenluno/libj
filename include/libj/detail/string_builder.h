// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STRING_BUILDER_H_
#define LIBJ_DETAIL_STRING_BUILDER_H_

#include <libj/this.h>
#include <libj/symbol.h>
#include <libj/detail/to_string.h>

#include <assert.h>

namespace libj {
namespace detail {

template<typename I>
class StringBuilder : public I {
 public:
    typedef typename I::Ptr Ptr;
    typedef typename I::CPtr CPtr;

    virtual Size length() const {
        return buf_.length();
    }

    virtual Char charAt(Size index) const {
        if (index >= buf_.length()) {
            return NO_CHAR;
        } else {
            return buf_[index];
        }
    }

    virtual Ptr append(const Value& val) {
        LIBJ_STATIC_SYMBOL_DEF(symNull,      "null");
        LIBJ_STATIC_SYMBOL_DEF(symUndefined, "undefined");

        if (val.isObject()) {
            String::CPtr s = toCPtr<Object>(val)->toString();
            if (s) {
                buf_.append(s->data());
            } else {
                assert(false);
                buf_.append(symNull->data());
            }
        } else if (val.isPrimitive()) {
            const Size kLen = 64;
            char buf[kLen];
            if (primitiveToString(val, buf, kLen)) {
                return StringBuilder::appendCStr(buf);
            } else {
                assert(false);
                buf_.append(symNull->data());
            }
        } else if (val.isNull()) {
            buf_.append(symNull->data());
        } else {
            assert(val.isUndefined());
            buf_.append(symUndefined->data());
        }
        return LIBJ_THIS_PTR(I);
    }

    virtual Ptr appendChar(Char c) {
        buf_.push_back(c);
        return LIBJ_THIS_PTR(I);
    }

    virtual Ptr appendCStr(const char* cstr) {
        LIBJ_STATIC_SYMBOL_DEF(symNull, "null");

        if (cstr) {
            while (Char c = static_cast<Char>(*cstr++)) {
                buf_.push_back(c);
            }
        } else {
            buf_.append(symNull->data());
        }
        return LIBJ_THIS_PTR(I);
    }

    virtual Boolean setCharAt(Size index, Char c) {
        if (index >= buf_.length()) {
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

#endif  // LIBJ_DETAIL_STRING_BUILDER_H_
