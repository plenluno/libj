// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STRING_H_
#define LIBJ_DETAIL_STRING_H_

#include <libj/cast.h>
#include <libj/constant.h>
#include <libj/exception.h>
#include <libj/map.h>
#include <libj/string.h>
#include <libj/glue/cvtutf.h>
#include <libj/detail/mutex.h>

#include <assert.h>
#include <string>
#include <vector>

namespace libj {
namespace detail {

glue::UnicodeEncoding convertStrEncoding(libj::String::Encoding enc) {
    switch (enc) {
    case libj::String::UTF8:
        return glue::UTF8;
    case libj::String::UTF16BE:
        return glue::UTF16BE;
    case libj::String::UTF16LE:
        return glue::UTF16LE;
    case libj::String::UTF32BE:
        return glue::UTF32BE;
    case libj::String::UTF32LE:
        return glue::UTF32LE;
    default:
        assert(false);
        return glue::UTF8;
    }
}

class String : public libj::String {
#ifdef LIBJ_USE_UTF32

 public:
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
        : str_(glue::toUtf32(data, convertStrEncoding(enc), max))
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

    virtual CPtr concat(CPtr other) const {
        if (!other || other->isEmpty()) {
            return this->toString();
        } else if (this->isEmpty()) {
            return other->toString();
        }

        const String* that = static_cast<const String*>(&(*other));
        String* s = new String(*this);
        s->str_ += that->str_;
        return CPtr(s);
    }

    virtual Int compareTo(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return result;
        }

        CPtr other = LIBJ_STATIC_CPTR_CAST(libj::String)(that);
        Size len1 = this->length();
        Size len2 = other->length();
        Size len = len1 < len2 ? len1 : len2;
        for (Size i = 0; i < len; i++) {
            Char c1 = this->charAt(i);
            Char c2 = other->charAt(i);
            if (c1 != c2) {
                return c1 - c2;
            }
        }
        return len1 - len2;
    }

    virtual Boolean equals(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return !result;
        }

        CPtr other = LIBJ_STATIC_CPTR_CAST(libj::String)(that);
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
                    if (c1 != c2) {
                        return false;
                    }
                }
                return true;
            }
        }
    }

    virtual Boolean startsWith(CPtr other, Size from) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < from + len2) {
            return false;
        }

        for (Size i = 0; i < len2; i++) {
            if (this->charAt(from + i) != other->charAt(i)) {
                return false;
            }
        }
        return true;
    }

    virtual Boolean endsWith(CPtr other) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2) {
            return false;
        }

        Size pos = len1 - len2;
        for (Size i = 0; i < len2; i++) {
            if (this->charAt(pos + i) != other->charAt(i)) {
                return false;
            }
        }
        return true;
    }

    virtual Size indexOf(Char c, Size from) const {
        Size len = length();
        for (Size i = from; i < len; i++) {
            if (charAt(i) == c) {
                return i;
            }
        }
        return NO_POS;
    }

    virtual Size indexOf(CPtr other, Size from) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < from + len2) {
            return NO_POS;
        }

        Size n = len1 - len2 + 1;
        for (Size i = from; i < n; i++) {
            if (startsWith(other, i)) {
                return i;
            }
        }
        return NO_POS;
    }

    virtual Size lastIndexOf(Char c, Size from) const {
        Size len = length();
        if (len == 0)
            return NO_POS;
        from = from < len ? from : len - 1;
        for (Size i = from; ; i--) {
            if (charAt(i) == c) {
                return i;
            } else if (i == 0) {
                break;
            }
        }
        return NO_POS;
    }

    virtual Size lastIndexOf(CPtr other, Size from) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2) {
            return NO_POS;
        }

        Size diff = len1 - len2;
        from = from < diff ? from : diff;
        for (Size i = from; ; i--) {
            if (startsWith(other, i)) {
                return i;
            } else if (i == 0) {
                break;
            }
        }
        return NO_POS;
    }

    virtual CPtr toLowerCase() const {
        Size len = length();
        String* s = new String();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'A' && c <= 'Z') {
                c += 'a' - 'A';
            }
            s->str_ += c;
        }
        return CPtr(s);
    }

    virtual CPtr toUpperCase() const {
        Size len = length();
        String* s = new String();
        for (Size i = 0; i < len; i++) {
            Char c = charAt(i);
            if (c >= 'a' && c <= 'z') {
                c -= 'a' - 'A';
            }
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
        return glue::fromUtf32(str_, convertStrEncoding(enc));
    }

 private:
    class CharIterator : public TypedIterator<Char> {
        friend class String;
        typedef std::u32string::const_iterator CItr;

     public:
        virtual Boolean hasNext() const {
            return pos_ != end_;
        }

        virtual Char next() {
            if (pos_ == end_) {
                LIBJ_THROW(Error::NO_SUCH_ELEMENT);
                return 0;
            } else {
                Char c = *pos_;
                ++pos_;
                return c;
            }
        }

        virtual libj::String::CPtr toString() const {
            return libj::String::create();
        }

     private:
        CItr pos_;
        CItr end_;

        CharIterator(const std::u32string& str)
            : pos_(str.begin())
            , end_(str.end()) {}
    };

 private:
    std::u32string str_;

#else  // LIBJ_USE_UTF32

 public:
    String()
        : length_(0)
        , interned_(false) {}

    String(Char c, Size n)
        : length_(n)
        , interned_(false) {
        std::u32string u32s(n, c);
        str_ = glue::fromUtf32(u32s, glue::UTF8);
    }

    String(const std::u16string& s16)
        : interned_(false) {
        str_ = glue::utf16ToUtf8(s16, &length_);
    }

    String(const std::u32string& s32)
        : str_(glue::fromUtf32(s32, glue::UTF8))
        , length_(s32.length())
        , interned_(false) {}

    String(const String& other)
        : str_(other.str_)
        , length_(other.length_)
        , interned_(false) {}

    String(const String& other, Size pos, Size count = NO_POS)
        : interned_(false) {
        Size len = other.length() - pos;
        length_ = count < len ? count : len;

        const char* p0 = other.str_.c_str();
        const char* p1 = advance(p0, pos);
        const char* p2 = advance(p1, length_);
        str_ = std::string(other.str_, p1 - p0, p2 - p1);
    }

    String(
        const void* data,
        Encoding enc,
        Size max)
        : interned_(false) {
        str_ = glue::toUtf8(data, convertStrEncoding(enc), max, &length_);
    }

    virtual Size length() const {
        return length_;
    }

    virtual Char charAt(Size index) const {
        if (index >= length()) {
            return NO_CHAR;
        } else {
            const char* pos = advance(str_.c_str(), index);
            return glue::codePointAt(pos, glue::UTF8);
        }
    }

    virtual CPtr concat(CPtr other) const {
        if (!other || other->isEmpty()) {
            return this->toString();
        } else if (this->isEmpty()) {
            return other->toString();
        }

        const String* that = static_cast<const String*>(&(*other));
        String* s = new String(*this);
        s->str_ += that->str_;
        s->length_ += that->length_;
        return CPtr(s);
    }

    virtual Int compareTo(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return result;
        }

        CPtr other = LIBJ_STATIC_CPTR_CAST(libj::String)(that);
        Size len1 = this->length();
        Size len2 = other->length();
        Size len = len1 < len2 ? len1 : len2;
        TypedIterator<Char>::Ptr itr1 = this->iterator();
        TypedIterator<Char>::Ptr itr2 = other->iterator();
        for (Size i = 0; i < len; i++) {
            assert(itr1->hasNext() && itr2->hasNext());
            Char c1 = itr1->next();
            Char c2 = itr2->next();
            if (c1 != c2) {
                return c1 - c2;
            }
        }
        return len1 - len2;
    }

    virtual Boolean equals(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return !result;
        }

        CPtr other = LIBJ_STATIC_CPTR_CAST(libj::String)(that);
        if (this->isInterned() && other->isInterned()) {
            return false;
        } else {
            Size len = this->length();
            if (other->length() != len) {
                return false;
            } else {
                TypedIterator<Char>::Ptr itr1 = this->iterator();
                TypedIterator<Char>::Ptr itr2 = other->iterator();
                for (Size i = 0; i < len; i++) {
                    assert(itr1->hasNext() && itr2->hasNext());
                    Char c1 = itr1->next();
                    Char c2 = itr2->next();
                    if (c1 != c2) {
                        return false;
                    }
                }
                return true;
            }
        }
    }

    virtual Boolean startsWith(CPtr other, Size from) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < from + len2) {
            return false;
        }

        const char* this8 = advance(this->str_.c_str(), from);
        const String* that = static_cast<const String*>(&(*other));
        const char* that8 = that->str_.c_str();
        Size len8 = that->str_.length();

        for (Size i = 0; i < len8; i++, this8++, that8++) {
            if (*this8 != *that8) {
                return false;
            }
        }
        return true;
    }

    virtual Boolean endsWith(CPtr other) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2) {
            return false;
        }

        const char* this8 = advance(this->str_.c_str(), len1 - len2);
        const String* that = static_cast<const String*>(&(*other));
        const char* that8 = that->str_.c_str();
        Size len8 = that->str_.length();

        for (Size i = 0; i < len8; i++, this8++, that8++) {
            if (*this8 != *that8) {
                return false;
            }
        }
        return true;
    }

    virtual Size indexOf(Char c, Size from) const {
        if (from >= length_) return NO_POS;

        Size i = 0;
        TypedIterator<Char>::Ptr itr = iterator();
        for (; i < from; i++) {
            itr->next();
        }
        while (itr->hasNext()) {
            if (itr->next() == c) {
                return i;
            } else {
                i++;
            }
        }
        return NO_POS;
    }

    virtual Size indexOf(CPtr other, Size from) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < from + len2) {
            return NO_POS;
        }

        Size n = len1 - len2 + 1;
        const String* that = static_cast<const String*>(&(*other));
        const char* s1 = advance(str_.c_str(), from);
        const char* s2 = that->str_.c_str();
        for (Size i = from; i < n; i++) {
            if (isSame(s1, s2, len2)) {
                return i;
            } else {
                s1 += glue::byteLengthAt(s1, glue::UTF8);
            }
        }
        return NO_POS;
    }

    virtual Size lastIndexOf(Char c, Size from) const {
        Size len = length();
        if (len == 0) {
            return NO_POS;
        }

        from = from < len ? from : len - 1;
        std::vector<Size> byteLens;
        const char* pos = str_.c_str();
        for (Size i = 0; i < from; i++) {
            Size byteLen = glue::byteLengthAt(pos, glue::UTF8);
            byteLens.push_back(byteLen);
            pos += byteLen;
        }
        for (Size i = from; ; i--) {
            if (glue::codePointAt(pos, glue::UTF8) == c) {
                return i;
            } else if (i == 0) {
                break;
            } else {
                pos -= byteLens[i - 1];
            }
        }
        return NO_POS;
    }

    virtual Size lastIndexOf(CPtr other, Size from) const {
        // TODO(plenluno): make it more efficient
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2) {
            return NO_POS;
        }

        Size diff = len1 - len2;
        from = from < diff ? from : diff;

        std::vector<Size> byteLens;
        const char* s1 = str_.c_str();
        for (Size i = 0; i < from; i++) {
            Size byteLen = glue::byteLengthAt(s1, glue::UTF8);
            byteLens.push_back(byteLen);
            s1 += byteLen;
        }

        const String* that = static_cast<const String*>(&(*other));
        const char* s2 = that->str_.c_str();

        for (Size i = from; ; i--) {
            if (isSame(s1, s2, len2)) {
                return i;
            } else if (i == 0) {
                break;
            } else {
                s1 -= byteLens[i - 1];
            }
        }
        return NO_POS;
    }

    virtual CPtr toLowerCase() const {
        String* s = new String();
        s->length_ = length_;
        Size len = str_.length();
        const char* pos = str_.c_str();
        for (Size i = 0; i < len;) {
            Size byteLen = glue::byteLengthAt(pos, glue::UTF8);
            if (byteLen == 1) {
                char c = *pos++;
                if (c >= 'A' && c <= 'Z') {
                    c += 'a' - 'A';
                }
                s->str_ += c;
            } else {
                for (Size j = 0; j < byteLen; j++) {
                    s->str_ += *pos++;
                }
            }
            i += byteLen;
        }
        return CPtr(s);
    }

    virtual CPtr toUpperCase() const {
        String* s = new String();
        s->length_ = length_;
        Size len = str_.length();
        const char* pos = str_.c_str();
        for (Size i = 0; i < len;) {
            Size byteLen = glue::byteLengthAt(pos, glue::UTF8);
            if (byteLen == 1) {
                char c = *pos++;
                if (c >= 'a' && c <= 'z') {
                    c -= 'a' - 'A';
                }
                s->str_ += c;
            } else {
                for (Size j = 0; j < byteLen; j++) {
                    s->str_ += *pos++;
                }
            }
            i += byteLen;
        }
        return CPtr(s);
    }

    virtual CPtr toString() const {
        return CPtr(new String(*this));
    }

    virtual std::u16string toStdU16String() const {
        return glue::utf8ToUtf16(str_);
    }

    virtual std::u32string toStdU32String() const {
        return glue::toUtf32(str_.c_str(), glue::UTF8, NO_POS);
    }

    virtual std::string toStdString(Encoding enc) const {
        return glue::fromUtf8(str_, convertStrEncoding(enc));
    }

 private:
    class CharIterator : public TypedIterator<Char> {
        friend class String;

     public:
        virtual Boolean hasNext() const {
            return pos_ < end_;
        }

        virtual Char next() {
            if (pos_ >= end_) {
                LIBJ_THROW(Error::NO_SUCH_ELEMENT);
                return 0;
            } else {
                Char c = glue::codePointAt(pos_, glue::UTF8);
                pos_ += glue::byteLengthAt(pos_, glue::UTF8);
                return c;
            }
        }

        virtual libj::String::CPtr toString() const {
            return libj::String::create();
        }

     private:
        const char* pos_;
        const char* end_;

        CharIterator(const std::string& str)
            : pos_(str.c_str())
            , end_(pos_ + str.length()) {}
    };

    static const char* advance(const char* utf8, Size n) {
        const char* pos = utf8;
        for (Size i = 0; i < n; i++) {
            pos += glue::byteLengthAt(pos, glue::UTF8);
        }
        return pos;
    }

    static Boolean isSame(const char* s1, const char* s2, Size n) {
        for (Size i = 0; i < n; i++) {
            Size byteLen1 = glue::byteLengthAt(s1, glue::UTF8);
            Size byteLen2 = glue::byteLengthAt(s2, glue::UTF8);
            if (byteLen1 != byteLen2) return false;

            char32_t c1 = glue::codePointAt(s1, glue::UTF8);
            char32_t c2 = glue::codePointAt(s2, glue::UTF8);
            if (c1 != c2) return false;

            s1 += byteLen1;
            s2 += byteLen2;
        }
        return true;
    }

 private:
    std::string str_;
    Size length_;

#endif  // LIBJ_USE_UTF32

 public:
    virtual CPtr substring(Size from) const {
        if (from > length()) {
            return libj::String::null();
        } else if (from == 0) {
            return toString();
        } else {
            return CPtr(new String(*this, from));
        }
    }

    virtual CPtr substring(Size from, Size to) const {
        Size len = length();
        if (from > len || to > len || from > to) {
            return libj::String::null();
        } else if (from == 0 && to == len) {
            return toString();
        } else {
            return CPtr(new String(*this, from, to - from));
        }
    }

    virtual Boolean isEmpty() const {
        return length() == 0;
    }

    virtual TypedIterator<Char>::Ptr iterator() const {
        return TypedIterator<Char>::Ptr(new CharIterator(str_));
    }

 public:
    static CPtr intern(CPtr str) {
        static const Map::Ptr symbols = Map::create();
#ifdef LIBJ_USE_THREAD
        static detail::Mutex mutex;
#endif

        if (!str || str->isInterned()) return str;

        CPtr sym;
#ifdef LIBJ_USE_THREAD
        mutex.lock();
        sym = toCPtr<libj::String>(symbols->get(str));
        mutex.unlock();
#else
        sym = toCPtr<libj::String>(symbols->get(str));
#endif
        if (sym) {
            return sym;
        } else {
            String* s = new String(*(static_cast<const String*>(&(*str))));
            s->interned_ = true;

            CPtr sp(s);
#ifdef LIBJ_USE_THREAD
            mutex.lock();
            symbols->put(sp, sp);
            mutex.unlock();
#else
            symbols->put(sp, sp);
#endif
            return sp;
        }
    }

    virtual Boolean isInterned() const {
        return interned_;
    }

 private:
    Boolean interned_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_STRING_H_
