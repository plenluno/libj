// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STRING_H_
#define LIBJ_DETAIL_STRING_H_

#include <libj/cast.h>
#include <libj/constant.h>
#include <libj/map.h>
#include <libj/glue/cvtutf.h>

#include <assert.h>
#include <string>

namespace libj {
namespace detail {

template<typename I>
class String : public I {
 public:
    typedef typename I::CPtr CPtr;
    typedef typename I::Encoding Encoding;

    String()
        : str_()
        , interned_(false) {}

    String(Char c, Size n)
        : str_(n, c)
        , interned_(false) {}

    String(const std::u16string& s16)
        : str_(glue::utf16ToUtf32(s16))
        , interned_(false) {}

    String(const std::u32string& s32)
        : str_(s32)
        , interned_(false) {}

    String(const String& other)
        : str_(other.str_)
        , interned_(false) {}

    String(const String& other, Size pos, Size count = NO_POS)
        : str_(other.str_, pos, count)
        , interned_(false) {}

    String(
        const void* data,
        Encoding enc,
        Size max)
        : str_(glue::toUtf32(data, convertEncoding(enc), max))
        , interned_(false) {}

    virtual Size length() const {
        return str_.length();
    }

    virtual Char charAt(Size index) const {
        if (index >= length()) {
            return NO_CHAR;
        } else {
            return str_.at(index);
        }
    }

    virtual CPtr substring(Size from) const {
        if (from > length()) {
            return I::null();
        } else if (from == 0) {
            return toString();
        } else {
            return CPtr(new String(*this, from));
        }
    }

    virtual CPtr substring(Size from, Size to) const {
        Size len = length();
        if (from > len || to > len || from > to) {
            return I::null();
        } else if (from == 0 && to == len) {
            return toString();
        } else {
            return CPtr(new String(*this, from, to - from));
        }
    }

    virtual CPtr concat(CPtr other) const {
        if (!other || other->isEmpty()) {
            return this->toString();
        } else if (this->isEmpty()) {
            return other->toString();
        }

        String* s = new String(*this);
        Size len = other->length();
        for (Size i = 0; i < len; i++)
            s->str_.push_back(other->charAt(i));
        return CPtr(s);
    }

    virtual Int compareTo(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return result;
        }

        String::CPtr other = LIBJ_STATIC_CPTR_CAST(I)(that);
        Size len1 = this->length();
        Size len2 = other->length();
        Size len = len1 < len2 ? len1 : len2;
        for (Size i = 0; i < len; i++) {
            Char c1 = this->charAt(i);
            Char c2 = other->charAt(i);
            if (c1 != c2)
                return c1 - c2;
        }
        return len1 - len2;
    }

    virtual Boolean equals(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return !result;
        }

        String::CPtr other = LIBJ_STATIC_CPTR_CAST(String)(that);
        if (this->isInterned() && other->isInterned()) {
            return false;
        } else {
            Size len = this->length();
            if (other->length() != len) {
                return false;
            } else {
                for (Size i = 0; i < len; i++) {
                    Char c1 = this->charAt(i);
                    Char c2 = other->charAt(i);
                    if (c1 != c2)
                        return false;
                }
                return true;
            }
        }
    }

    virtual Boolean startsWith(CPtr other, Size from) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < from + len2)
            return false;
        for (Size i = 0; i < len2; i++)
            if (this->charAt(from + i) != other->charAt(i))
                return false;
        return true;
    }

    virtual Boolean endsWith(CPtr other) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2)
            return false;
        Size pos = len1 - len2;
        for (Size i = 0; i < len2; i++)
            if (this->charAt(pos + i) != other->charAt(i))
                return false;
        return true;
    }

    virtual Size indexOf(Char c, Size from) const {
        Size len = length();
        for (Size i = from; i < len; i++)
            if (charAt(i) == c)
                return i;
        return NO_POS;
    }

    virtual Size indexOf(CPtr other, Size from) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < from + len2)
            return NO_POS;
        Size n = len1 - len2 + 1;
        for (Size i = from; i < n; i++)
            if (startsWith(other, i))
                return i;
        return NO_POS;
    }

    virtual Size lastIndexOf(Char c, Size from) const {
        Size len = length();
        if (len == 0)
            return NO_POS;
        from = from < len ? from : len - 1;
        for (Size i = from; ; i--) {
            if (charAt(i) == c)
                return i;
            if (i == 0)
                break;
        }
        return NO_POS;
    }

    virtual Size lastIndexOf(CPtr other, Size from) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2)
            return NO_POS;
        Size diff = len1 - len2;
        from = from < diff ? from : diff;
        for (Size i = from; ; i--) {
            if (startsWith(other, i))
                return i;
            if (i == 0)
                break;
        }
        return NO_POS;
    }

    virtual Boolean isEmpty() const {
        return length() == 0;
    }

    virtual Boolean isInterned() const {
        return interned_;
    }

    virtual CPtr toLowerCase() const {
        Size len = length();
        String* s = new String();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'A' && c <= 'Z')
                c += 'a' - 'A';
            s->str_ += c;
        }
        return CPtr(s);
    }

    virtual CPtr toUpperCase() const {
        Size len = length();
        String* s = new String();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'a' && c <= 'z')
                c -= 'a' - 'A';
            s->str_ += c;
        }
        return CPtr(s);
    }

    virtual CPtr toString() const {
        return CPtr(new String(*this));
    }

    virtual std::u16string toStdU16String() const {
        return glue::utf32ToUtf16(str_);
    }

    virtual std::u32string toStdU32String() const {
        return str_;
    }

    virtual std::string toStdString(Encoding enc) const {
        return glue::fromUtf32(str_, convertEncoding(enc));
    }

 public:
    static CPtr intern(CPtr str) {
        static const Map::Ptr symbols = Map::create();

        if (!str || str->isInterned()) return str;

        CPtr sym = toCPtr<I>(symbols->get(str));
        if (sym) {
            return sym;
        } else {
            String* s = new String();
            s->interned_ = true;
            Size len = str->length();
            for (Size i = 0; i < len; i++) {
                s->str_.push_back(str->charAt(i));
            }
            CPtr sp(s);
            symbols->put(sp, sp);
            return sp;
        }
    }

 private:
    static glue::UnicodeEncoding convertEncoding(Encoding enc) {
        switch (enc) {
        case I::UTF8:
            return glue::UTF8;
        case I::UTF16BE:
            return glue::UTF16BE;
        case I::UTF16LE:
            return glue::UTF16LE;
        case I::UTF32BE:
            return glue::UTF32BE;
        case I::UTF32LE:
            return glue::UTF32LE;
        default:
            assert(false);
            return glue::UTF8;
        }
    }

 private:
    std::u32string str_;
    Boolean interned_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_STRING_H_
