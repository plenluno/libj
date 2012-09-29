// Copyright (c) 2012 Plenluno All rights reserved.

#include <assert.h>
#include <stdio.h>
#include <iv/lv5/third_party/v8_dtoa/conversions.h>
#include <string>

#include "libj/string.h"
#include "./glue/cvtutf.h"

namespace libj {

class StringImpl : public String {
 public:
    Size length() const {
        return str_.length();
    }

    Char charAt(Size index) const {
        if (index >= length()) {
            return NO_CHAR;
        } else {
            return str_.at(index);
        }
    }

    CPtr substring(Size from) const {
        if (from > length()) {
            return null();
        } else if (from == 0) {
            return toString();
        } else {
            CPtr p(new StringImpl(*this, from));
            return p;
        }
    }

    CPtr substring(Size from, Size to) const {
        Size len = length();
        if (from > len || to > len || from > to) {
            return null();
        } else if (from == 0 && to == len) {
            return toString();
        } else {
            CPtr p(new StringImpl(*this, from, to - from));
            return p;
        }
    }

    CPtr concat(CPtr other) const {
        if (!other || other->isEmpty()) {
            return this->toString();
        } else if (this->isEmpty()) {
            return other->toString();
        }

        StringImpl* s = new StringImpl(*this);
        Size len = other->length();
        for (Size i = 0; i < len; i++)
            s->str_.push_back(other->charAt(i));
        CPtr p(s);
        return p;
    }

    Int compareTo(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return result;
        }

        String::CPtr other = LIBJ_STATIC_CPTR_CAST(String)(that);
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

    Boolean startsWith(CPtr other, Size from) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < from + len2)
            return false;
        for (Size i = 0; i < len2; i++)
            if (this->charAt(from + i) != other->charAt(i))
                return false;
        return true;
    }

    Boolean endsWith(CPtr other) const {
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

    Size indexOf(Char c, Size from) const {
        Size len = length();
        for (Size i = from; i < len; i++)
            if (charAt(i) == c)
                return i;
        return NO_POS;
    }

    Size indexOf(CPtr other, Size from) const {
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

    Size lastIndexOf(Char c, Size from) const {
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

    Size lastIndexOf(CPtr other, Size from) const {
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

    Boolean isEmpty() const {
        return length() == 0;
    }

    CPtr toLowerCase() const {
        Size len = length();
        StringImpl* s = new StringImpl();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'A' && c <= 'Z')
                c += 'a' - 'A';
            s->str_ += c;
        }
        CPtr p(s);
        return p;
    }

    CPtr toUpperCase() const {
        Size len = length();
        StringImpl* s = new StringImpl();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'a' && c <= 'z')
                c -= 'a' - 'A';
            s->str_ += c;
        }
        CPtr p(s);
        return p;
    }

    CPtr toString() const {
        CPtr p(new StringImpl(*this));
        return p;
    }

    std::u16string toStdU16String() const {
        return glue::utf32ToUtf16(str_);
    }

    std::u32string toStdU32String() const {
        return str_;
    }

    std::string toStdString(Encoding enc) const {
        return glue::fromUtf32(str_, convertEncoding(enc));
    }

    static CPtr create() {
        CPtr p(new StringImpl());
        return p;
    }

    static CPtr create(Char c, Size n) {
        CPtr p(new StringImpl(c, n));
        return p;
    }

    static CPtr create(const std::u16string& s16) {
        CPtr p(new StringImpl(s16));
        return p;
    }

    static CPtr create(const std::u32string& s32) {
        CPtr p(new StringImpl(s32));
        return p;
    }

    static CPtr create(const void* data, Encoding enc, Size max) {
        CPtr p(new StringImpl(data, enc, max));
        return p;
    }

 private:
    static glue::UnicodeEncoding convertEncoding(Encoding enc) {
        switch (enc) {
        case UTF8:
            return glue::UTF8;
        case UTF16BE:
            return glue::UTF16BE;
        case UTF16LE:
            return glue::UTF16LE;
        case UTF32BE:
            return glue::UTF32BE;
        case UTF32LE:
            return glue::UTF32LE;
        default:
            assert(false);
        }
    }

 private:
    std::u32string str_;

    StringImpl() : str_() {}

    StringImpl(Char c, Size n) : str_(n, c) {}

    StringImpl(const std::u16string& s16)
        : str_(glue::utf16ToUtf32(s16)) {}

    StringImpl(const std::u32string& s32) : str_(s32) {}

    StringImpl(const void* data, Encoding enc, Size max)
        : str_(glue::toUtf32(data, convertEncoding(enc), max)) {}

    StringImpl(const StringImpl& other) : str_(other.str_) {}

    StringImpl(const StringImpl& other, Size pos, Size count = NO_POS)
        : str_(other.str_, pos, count) {}
};

String::CPtr String::create() {
    static const String::CPtr empty =
        StringImpl::create(NULL, UTF8, NO_POS);
    return empty;
}

String::CPtr String::create(Char c, Size n) {
    return StringImpl::create(c, n);
}

String::CPtr String::create(const std::u16string& s16) {
    return StringImpl::create(s16);
}

String::CPtr String::create(const std::u32string& s32) {
    return StringImpl::create(s32);
}

String::CPtr String::create(const void* data, Encoding enc, Size max) {
    return StringImpl::create(data, enc, max);
}

static String::CPtr LIBJ_STR_TRUE = String::create("true");
static String::CPtr LIBJ_STR_FALSE = String::create("false");

static String::CPtr booleanToString(const Value& val) {
    Boolean b;
    to<Boolean>(val, &b);
    return b ? LIBJ_STR_TRUE : LIBJ_STR_FALSE;
}

static String::CPtr byteToString(const Value& val) {
    Byte b;
    to<Byte>(val, &b);
    const Size kLen = (8 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", b);
    return String::create(s);
}

static String::CPtr ubyteToString(const Value& val) {
    UByte ub;
    to<UByte>(val, &ub);
    const Size kLen = (8 / 3) + 2;
    char s[kLen];
    snprintf(s, kLen, "%d", ub);
    return String::create(s);
}

static String::CPtr shortToString(const Value& val) {
    Short sh;
    to<Short>(val, &sh);
    const Size kLen = (16 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", sh);
    return String::create(s);
}

static String::CPtr ushortToString(const Value& val) {
    UShort ush;
    to<UShort>(val, &ush);
    const Size kLen = (16 / 3) + 2;
    char s[kLen];
    snprintf(s, kLen, "%d", ush);
    return String::create(s);
}

static String::CPtr intToString(const Value& val) {
    Int i;
    to<Int>(val, &i);
    const Size kLen = (32 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", i);
    return String::create(s);
}

static String::CPtr uintToString(const Value& val) {
    UInt ui;
    to<UInt>(val, &ui);
    const Size kLen = (32 / 3) + 2;
    char s[kLen];
    snprintf(s, kLen, "%d", ui);
    return String::create(s);
}

static String::CPtr longToString(const Value& val) {
    Long l;
    to<Long>(val, &l);
    const Size kLen = (64 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%lld", l);
    return String::create(s);
}

static String::CPtr ulongToString(const Value& val) {
    ULong ul;
    to<ULong>(val, &ul);
    const Size kLen = (64 / 3) + 2;
    char s[kLen];
    snprintf(s, kLen, "%lld", ul);
    return String::create(s);
}

static String::CPtr floatToString(const Value& val) {
    Float f;
    to<Float>(val, &f);
    const Size kLen = 64;
    char s[kLen];
    return String::create(v8::internal::DoubleToCString(f, s, kLen));
}

static String::CPtr doubleToString(const Value& val) {
    Double d;
    to<Double>(val, &d);
    const Size kLen = 64;
    char s[kLen];
    return String::create(v8::internal::DoubleToCString(d, s, kLen));
}

static String::CPtr sizeToString(const Value& val) {
    Size n;
    to<Size>(val, &n);
    const Size kLen = ((sizeof(Size) << 3) / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%zd", n);
    return String::create(s);
}

static String::CPtr typeIdToString(const Value& val) {
    TypeId t;
    to<TypeId>(val, &t);
    const Size kLen = ((sizeof(TypeId) << 3) / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%zd", t);
    return String::create(s);
}

static String::CPtr objectToString(const Value& val) {
    Object::CPtr o = toCPtr<Object>(val);
    if (o) {
        return o->toString();
    } else {
        return String::null();
    }
}

String::CPtr String::valueOf(const Value& val) {
    if (val.isEmpty()) {
        return null();
    } else if (val.instanceof(Type<Object>::id())) {
        return objectToString(val);
    } else if (val.type() == Type<Boolean>::id()) {
        return booleanToString(val);
    } else if (val.type() == Type<Byte>::id()) {
        return byteToString(val);
    } else if (val.type() == Type<UByte>::id()) {
        return ubyteToString(val);
    } else if (val.type() == Type<Short>::id()) {
        return shortToString(val);
    } else if (val.type() == Type<UShort>::id()) {
        return ushortToString(val);
    } else if (val.type() == Type<Int>::id()) {
        return intToString(val);
    } else if (val.type() == Type<UInt>::id()) {
        return uintToString(val);
    } else if (val.type() == Type<Long>::id()) {
        return longToString(val);
    } else if (val.type() == Type<ULong>::id()) {
        return ulongToString(val);
    } else if (val.type() == Type<Float>::id()) {
        return floatToString(val);
    } else if (val.type() == Type<Double>::id()) {
        return doubleToString(val);
    } else if (val.type() == Type<Size>::id()) {
        return sizeToString(val);
    } else if (val.type() == Type<TypeId>::id()) {
        return typeIdToString(val);
    } else {
        return null();
    }
}

}  // namespace libj
