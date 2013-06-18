// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_STRING_H_
#define LIBJ_DETAIL_STRING_H_

#include <libj/cast.h>
#include <libj/constant.h>
#include <libj/debug_print.h>
#include <libj/exception.h>
#include <libj/string.h>
#include <libj/this.h>
#include <libj/typed_iterator.h>
#include <libj/glue/cvtutf.h>

#ifdef LIBJ_USE_THREAD
# include <libj/concurrent_map.h>
#else
# include <libj/map.h>
#endif

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

#define LIBJ_DETAIL_STRING(S) static_cast<const String*>(&(*S))
#define LIBJ_INTERNAL_STRING(S) LIBJ_DETAIL_STRING(S)->str_

class String : public libj::String {
    typedef TypedIterator<Char> Iterator;

#ifdef LIBJ_USE_UTF16

    typedef std::u16string ustring;

 public:
    String(const std::u16string& s16)
        : str_(s16)
        , interned_(false) {}

    String(const std::u32string& s32)
        : str_(glue::utf32ToUtf16(s32))
        , interned_(false) {}

    String(
        const void* data, Encoding enc, Size len, Size max)
        : str_(glue::toUtf16(data, convertStrEncoding(enc), len, max))
        , interned_(false) {}

    virtual std::string toStdString(Encoding enc) const {
        return glue::fromUtf16(str_, convertStrEncoding(enc));
    }

    virtual std::u16string toStdU16String() const {
        return str_;
    }

    virtual std::u32string toStdU32String() const {
        return glue::utf16ToUtf32(str_);
    }

#else  // LIBJ_USE_UTF16

    typedef std::u32string ustring;

 public:
    String(const std::u16string& s16)
        : str_(glue::utf16ToUtf32(s16))
        , interned_(false) {}

    String(const std::u32string& s32)
        : str_(s32)
        , interned_(false) {}

    String(
        const void* data, Encoding enc, Size len, Size max)
        : str_(glue::toUtf32(data, convertStrEncoding(enc), len, max))
        , interned_(false) {}

    virtual std::string toStdString(Encoding enc) const {
        return glue::fromUtf32(str_, convertStrEncoding(enc));
    }

    virtual std::u16string toStdU16String() const {
        return glue::utf32ToUtf16(str_);
    }

    virtual std::u32string toStdU32String() const {
        return str_;
    }

#endif  // LIBJ_USE_UTF16

 public:
    String()
        : str_()
        , interned_(false) {}

    String(Char c, Size n)
        : str_(n, c)
        , interned_(false) {}

    String(const String& other)
        : str_(other.str_)
        , interned_(false) {}

    String(const String& other, Size pos, Size count = NO_POS)
        : str_(other.str_, pos, count)
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
        if (!other) {
            return String::null();
        } else if (other->isEmpty()) {
            return this->toString();
        } else if (this->isEmpty()) {
            return other->toString();
        }

        String* s = new String(*this);
        s->str_ += LIBJ_INTERNAL_STRING(other);
        return CPtr(s);
    }

    virtual Int compareTo(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return result;
        }

        assert(!!that);
        CPtr other = LIBJ_STATIC_CPTR_CAST(libj::String)(that);
        return str_.compare(LIBJ_INTERNAL_STRING(other));
    }

    virtual Boolean equals(Object::CPtr that) const {
        Int result = Object::compareTo(that);
        if (result != TYPE_CMP_SAME &&
            result != -TYPE_CMP_SAME) {
            return !result;
        }

        assert(!!that);
        CPtr other = LIBJ_STATIC_CPTR_CAST(libj::String)(that);
        return str_ == LIBJ_INTERNAL_STRING(other);
    }

    virtual Boolean startsWith(CPtr other, Size from) const {
        if (!other) return false;

        return !str_.compare(
            from,
            other->length(),
            LIBJ_INTERNAL_STRING(other));
    }

    virtual Boolean endsWith(CPtr other) const {
        if (!other) return false;

        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < len2) {
            return false;
        }

        return !str_.compare(
            len1 - len2,
            len2,
            LIBJ_INTERNAL_STRING(other));
    }

    virtual Size indexOf(Char c, Size from) const {
        return str_.find_first_of(c, from);
    }

    virtual Size indexOf(CPtr other, Size from) const {
        if (!other) return NO_POS;

        return str_.find(LIBJ_INTERNAL_STRING(other), from);
    }

    virtual Size lastIndexOf(Char c, Size from) const {
        return str_.find_last_of(c, from);
    }

    virtual Size lastIndexOf(CPtr other, Size from) const {
        if (!other) return NO_POS;

        return str_.rfind(LIBJ_INTERNAL_STRING(other), from);
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

    virtual Boolean isEmpty() const {
        return length() == 0;
    }

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

    virtual CPtr toString() const {
        return LIBJ_THIS_CPTR(String);
    }

    virtual const Char* data() const {
        return str_.data();
    }

 public:
    static CPtr intern(CPtr str) {
#ifdef LIBJ_USE_THREAD
        typedef ConcurrentMap SymbolMap;
#else
        typedef Map SymbolMap;
#endif
        static SymbolMap::Ptr symbols = SymbolMap::null();
        if (!symbols) {
            symbols = SymbolMap::create();
            LIBJ_DEBUG_PRINT(
                "static: SymbolMap %p",
                LIBJ_DEBUG_OBJECT_PTR(symbols));
        }

        if (!str || str->isInterned()) return str;

        CPtr sym = toCPtr<libj::String>(symbols->get(str));
        if (sym) {
            return sym;
        } else {
            String* s = new String(*LIBJ_DETAIL_STRING(str));
            s->interned_ = true;

            CPtr sp(s);
            symbols->put(sp, sp);
            LIBJ_DEBUG_PRINT(
                "symbol: [%d: %s] %p",
                symbols->size(),
                sp->toStdString().c_str(),
                LIBJ_DEBUG_OBJECT_PTR(sp));
            return sp;
        }
    }

    virtual Boolean isInterned() const {
        return interned_;
    }

 private:
    class CharIterator : public Iterator {
        friend class String;
        typedef ustring::const_iterator CItr;

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

        CharIterator(const ustring& str)
            : pos_(str.begin())
            , end_(str.end()) {}

        CharIterator(const CharIterator* itr)
            : pos_(itr->pos_)
            , end_(itr->end_) {}
    };

 private:
    ustring str_;
    Boolean interned_;
};

#undef LIBJ_INTERNAL_STRING
#undef LIBJ_DETAIL_STRING

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_STRING_H_
