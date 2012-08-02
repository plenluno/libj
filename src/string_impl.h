// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef SRC_STRING_IMPL_H_
#define SRC_STRING_IMPL_H_

#include <ctype.h>
#include <string>

#include "libj/string.h"
#include "libj/value.h"

namespace libj {

class StringImpl : public String {
 public:
    Size length() const {
        return str8_ ? str8_->length() :
               str32_ ? str32_->length() : 0;
    }

    Char charAt(Size index) const {
        if (index >= length())
            return NO_CHAR;
        return str8_ ? str8_->at(index) :
               str32_ ? str32_->at(index) : NO_CHAR;
    }

    CPtr substring(Size begin) const {
        if (begin > length()) {
            LIBJ_NULL_CPTR(String, p);
            return p;
        } else if (begin == 0) {
            return toString();
        } else if (str8_) {
            CPtr p(new StringImpl(str8_, begin));
            return p;
        } else {  // if (str32_)
            CPtr p(new StringImpl(str32_, begin));
            return p;
        }
    }

    CPtr substring(Size begin, Size end) const {
        Size len = length();
        if (begin > len || end > len || begin > end) {
            LIBJ_NULL_CPTR(String, p);
            return p;
        } else if (begin == 0 && end == len) {
            return toString();
        } else if (str8_) {
            CPtr p(new StringImpl(str8_, begin, end - begin));
            return p;
        } else {  // if (str32_)
            CPtr p(new StringImpl(str32_, begin, end - begin));
            return p;
        }
    }

    CPtr concat(CPtr other) const {
        if (!other || other->isEmpty()) {
            return this->toString();
        } else if (this->isEmpty()) {
            return other->toString();
        }

        if (this->str8_ && other->isAscii()) {
            StringImpl* s = new StringImpl(str8_);
            Size len = other->length();
            for (Size i = 0; i < len; i++)
                s->str8_->push_back(static_cast<int8_t>(other->charAt(i)));
            CPtr p(s);
            return p;
        } else if (this->str8_ && !other->isAscii()) {
            StringImpl* s = new StringImpl();
            s->str32_ = new Str32();
            Size len = this->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(this->charAt(i));
            len = other->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(other->charAt(i));
            CPtr p(s);
            return p;
        } else if (this->str32_ && other->isAscii()) {
            StringImpl* s = new StringImpl(str32_);
            Size len = other->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(other->charAt(i));
            CPtr p(s);
            return p;
        } else {  // if (this->str32_ && !other->isAscii())
            StringImpl* s = new StringImpl(str32_);
            Size len = other->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(other->charAt(i));
            CPtr p(s);
            return p;
        }
    }

    Int compareTo(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result)
            return result;
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

    Boolean startsWith(CPtr other, Size offset) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < offset + len2)
            return false;
        for (Size i = 0; i < len2; i++)
            if (this->charAt(offset + i) != other->charAt(i))
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

    Size indexOf(Char c, Size offset) const {
        Size len = length();
        for (Size i = offset; i < len; i++)
            if (charAt(i) == c)
                return i;
        return NO_POS;
    }

    Size indexOf(CPtr other, Size offset) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < offset + len2)
            return NO_POS;
        Size n = len1 - len2 + 1;
        for (Size i = offset; i < n; i++)
            if (startsWith(other, i))
                return i;
        return NO_POS;
    }

    Size lastIndexOf(Char c, Size offset) const {
        Size len = length();
        if (len == 0)
            return NO_POS;
        for (Size i = offset < len ? offset : len-1; ; i--) {
            if (charAt(i) == c)
                return i;
            if (i == 0)
                break;
        }
        return NO_POS;
    }

    Size lastIndexOf(CPtr other, Size offset) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < offset + len2)
            return NO_POS;
        Size from = len1 - len2;
        from = offset < from ? offset : from;
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

    Boolean isAscii() const {
        return str8_ ? true : str32_ ? false : true;
    }

    CPtr toLowerCase() const {
        Size len = length();
        if (isAscii()) {
            Str8* s = new Str8();
            for (Size i = 0; i < len; i++) {
                char c = static_cast<char>(charAt(i));
                if (c >= 'A' && c <= 'Z')
                    c += 'a' - 'A';
                *s += c;
            }
            CPtr p(new StringImpl(s, 0));
            return p;
        } else {
            Str32* s = new Str32();
            for (Size i = 0; i < len; i++) {
                Char c = charAt(i);
                if (c >= 'A' && c <= 'Z')
                    c += 'a' - 'A';
                *s += c;
            }
            CPtr p(new StringImpl(0, s));
            return p;
        }
    }

    CPtr toUpperCase() const {
        Size len = length();
        if (isAscii()) {
            Str8* s = new Str8();
            for (Size i = 0; i < len; i++) {
                char c = static_cast<char>(charAt(i));
                if (c >= 'a' && c <= 'z')
                    c -= 'a' - 'A';
                *s += c;
            }
            CPtr p(new StringImpl(s, 0));
            return p;
        } else {
            Str32* s = new Str32();
            for (Size i = 0; i < len; i++) {
                Char c = charAt(i);
                if (c >= 'a' && c <= 'z')
                    c -= 'a' - 'A';
                *s += c;
            }
            CPtr p(new StringImpl(0, s));
            return p;
        }
    }

    CPtr toString() const {
        CPtr p(new StringImpl(this));
        return p;
    }

    std::string toStdString() const;
    std::u16string toStdU16String() const;
    std::u32string toStdU32String() const;

 public:
    static CPtr create(Char c, Size n);
    static CPtr create(const void* data, Encoding enc, Size max);

    typedef std::basic_string<char> Str8;
    typedef std::basic_string<Char> Str32;

    const Str8* getStr8() const {
        return str8_;
    }

    const Str32* getStr32() const {
        return str32_;
    }

 private:
    Str8* str8_;
    Str32* str32_;

    StringImpl()
        : str8_(0)
        , str32_(0) {}

    StringImpl(const Str8* s)
        : str8_(s ? new Str8(*s) : 0)
        , str32_(0) {}

    StringImpl(const Str32* s)
        : str8_(0)
        , str32_(s ? new Str32(*s) : 0) {}

    StringImpl(const Str8* s, Size pos, Size count = NO_POS)
        : str8_(s ? new Str8(*s, pos, count) : 0)
        , str32_(0) {}

    StringImpl(const Str32* s, Size pos, Size count = NO_POS)
        : str8_(0)
        , str32_(s ? new Str32(*s, pos, count) : 0) {}

    StringImpl(const char* data, Size count = NO_POS)
        : str8_(0)
        , str32_(0) {
        if (!data)
            return;
        for (Size i = 0; i < count; i++) {
            if (data[i] == 0) {
                str8_ = new Str8(data);
                return;
            }
        }
        str8_ = new Str8(data, count);
    }

    StringImpl(const Char* data, Size count = NO_POS)
        : str8_(0)
        , str32_(0) {
        if (!data)
            return;
        for (Size i = 0; i < count; i++) {
            if (data[i] == 0) {
                str32_ = new Str32(data);
                return;
            }
        }
        str32_ = new Str32(data, count);
    }

    StringImpl(Str8* s8, Str32* s32)
        : str8_(s8)
        , str32_(s32) {
    }

    StringImpl(const StringImpl* s)
        : str8_(s->str8_ ? new Str8(*(s->str8_)) : 0)
        , str32_(s->str32_ ? new Str32(*(s->str32_)) : 0) {
    }

    StringImpl(Char c, Size n)
        : str8_(isascii(c) ? new Str8(n, static_cast<char>(c)) : 0)
        , str32_(isascii(c) ? 0 : new Str32(n, c)) {
    }

 public:
    ~StringImpl() {
        delete str8_;
        delete str32_;
    }
};

}  // namespace libj

#endif  // SRC_STRING_IMPL_H_
