// Copyright (c) 2012 Plenluno All rights reserved.

#include <string>
#include "libj/string.h"

namespace libj {

const Size NO_POS = -1;
const Char NO_CHAR = -1;

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

    Cptr substring(Size begin) const {
        if (begin > length()) {
            Cptr p(static_cast<String*>(0));
            return p;
        } else if (begin == 0) {
            Cptr p(this);
            return p;
        } else if (str8_) {
            Cptr p(new StringImpl(str8_, begin));
            return p;
        } else {  // if (str32_)
            Cptr p(new StringImpl(str32_, begin));
            return p;
        }
    }

    Cptr substring(Size begin, Size end) const {
        Size len = length();
        if (begin > len || end > len || begin > end) {
            Cptr p(static_cast<String*>(0));
            return p;
        } else if (begin == 0 && end == len) {
            Cptr p(this);
            return p;
        } else if (str8_) {
            Cptr p(new StringImpl(str8_, begin, end - begin));
            return p;
        } else {  // if (str32_)
            Cptr p(new StringImpl(str32_, begin, end - begin));
            return p;
        }
    }

    Cptr concat(Cptr other) const {
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
            Cptr p(s);
            return p;
        } else if (this->str8_ && !other->isAscii()) {
            StringImpl* s = new StringImpl();
            s->str32_ = new Str32();
            Size len = this->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(other->charAt(i));
            len = other->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(other->charAt(i));
            Cptr p(s);
            return p;
        } else if (this->str32_ && other->isAscii()) {
            StringImpl* s = new StringImpl(str32_);
            Size len = this->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(other->charAt(i));
            Cptr p(s);
            return p;
        } else {  // if (this->str32_ && !other->isAscii())
            StringImpl* s = new StringImpl(str32_);
            Size len = this->length();
            for (Size i = 0; i < len; i++)
                s->str32_->push_back(other->charAt(i));
            Cptr p(s);
            return p;
        }
    }

    Int compareTo(Type<Object>::Cptr that) const {
        Int result = Object::compareTo(that);
        if (result)
            return result;
        Type<String>::Cptr other = LIBJ_STATIC_CPTR_CAST(String)(that);
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

    bool startsWith(Cptr other, Size offset) const {
        Size len1 = this->length();
        Size len2 = other->length();
        if (len1 < offset + len2)
            return false;
        for (Size i = 0; i < len2; i++)
            if (this->charAt(offset + i) != other->charAt(i))
                return false;
        return true;
    }

    bool endsWith(Cptr other) const {
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

    Size indexOf(Cptr other, Size offset) const {
        // TODO(PL): make it more efficient
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

    Size lastIndexOf(Cptr other, Size offset) const {
        // TODO(PL): make it more efficient
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

    bool isEmpty() const {
        return length() == 0;
    }

    bool isAscii() const {
        return str8_ ? true : str32_ ? false : true;
    }
    
    Cptr toLowerCase() const {
        Size len = length();
        if (isAscii()) {
            Str8* s = new Str8();
            for (Size i = 0; i < len; i++) {
                char c = static_cast<char>(charAt(i));
                if (c >= 'A' && c <= 'Z')
                    c += 'a' - 'A';
                *s += c;
            }
            Cptr p(new StringImpl(s, 0));
            return p;
        } else {
            Str32* s = new Str32();
            for (Size i = 0; i < len; i++) {
                Char c = charAt(i);
                if (c >= 'A' && c <= 'Z')
                    c += 'a' - 'A';
                *s += c;
            }
            Cptr p(new StringImpl(0, s));
            return p;
        }
    }
    
    Cptr toUpperCase() const {
        Size len = length();
        if (isAscii()) {
            Str8* s = new Str8();
            for (Size i = 0; i < len; i++) {
                char c = static_cast<char>(charAt(i));
                if (c >= 'a' && c <= 'z')
                    c -= 'a' - 'A';
                *s += c;
            }
            Cptr p(new StringImpl(s, 0));
            return p;
        } else {
            Str32* s = new Str32();
            for (Size i = 0; i < len; i++) {
                Char c = charAt(i);
                if (c >= 'a' && c <= 'z')
                    c -= 'a' - 'A';
                *s += c;
            }
            Cptr p(new StringImpl(0, s));
            return p;
        }
    }

    Cptr toString() const {
        Cptr p(new StringImpl(this));
        return p;
    }

 public:
    static Cptr create() {
        Cptr p(new StringImpl());
        return p;
    }

    static Cptr create(const void* data, Encoding enc, Size max) {
        // TODO(PL): temp
        if (enc == ASCII) {
            Cptr p(new StringImpl(static_cast<const char*>(data), max));
            return p;
        } else if (enc == UTF8) {
            // TODO(PL): use ConvertUTF8toUTF32
            Cptr p(new StringImpl());
            return p;
        } else {
            Cptr p(new StringImpl());
            return p;
        }
    }

 private:
    typedef std::basic_string<char> Str8;
    typedef std::basic_string<Char> Str32;

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

 public:
    ~StringImpl() {
        delete str8_;
        delete str32_;
    }
};

Type<String>::Cptr String::create() {
    return StringImpl::create();
}

Type<String>::Cptr String::create(const void* data, Encoding enc, Size max) {
    return StringImpl::create(data, enc, max);
}

static Type<String>::Cptr LIBJ_STR_TRUE = String::create("true");
static Type<String>::Cptr LIBJ_STR_FALSE = String::create("false");

static Type<String>::Cptr booleanToString(const Value& val) {
    Boolean b;
    to<Boolean>(val, &b);
    return b ? LIBJ_STR_TRUE : LIBJ_STR_FALSE;
}

static Type<String>::Cptr byteToString(const Value& val) {
    Byte b;
    to<Byte>(val, &b);
    const Size len = (8 / 3) + 3;
    char s[len];
    snprintf(s, len, "%d", b);
    return String::create(s);
}

static Type<String>::Cptr shortToString(const Value& val) {
    Short sh;
    to<Short>(val, &sh);
    const Size len = (16 / 3) + 3;
    char s[len];
    snprintf(s, len, "%d", sh);
    return String::create(s);
}

static Type<String>::Cptr intToString(const Value& val) {
    Int i;
    to<Int>(val, &i);
    const Size len = (32 / 3) + 3;
    char s[len];
    snprintf(s, len, "%d", i);
    Type<String>::Cptr p = String::create(s);
    return p;
}

static Type<String>::Cptr longToString(const Value& val) {
    Long l;
    to<Long>(val, &l);
    const Size len = (64 / 3) + 3;
    char s[len];
    snprintf(s, len, "%lld", l);
    return String::create(s);
}

static Type<String>::Cptr floatToString(const Value& val) {
    Float f;
    to<Float>(val, &f);
    const Size len = (32 / 3) + 5;
    char s[len];
    snprintf(s, len, "%f", f);
    return String::create(s);
}

static Type<String>::Cptr doubleToString(const Value& val) {
    Double d;
    to<Double>(val, &d);
    const Size len = (64 / 3) + 5;
    char s[len];
    snprintf(s, len, "%lf", d);
    return String::create(s);
}

static Type<String>::Cptr sizeToString(const Value& val) {
    Size n;
    to<Size>(val, &n);
    const Size len = (sizeof(Size) / 3) + 3;
    char s[len];
    snprintf(s, len, "%zd", n);
    Type<String>::Cptr p = String::create(s);
    return p;
}

static Type<String>::Cptr typeIdToString(const Value& val) {
    TypeId t;
    to<TypeId>(val, &t);
    const Size len = (sizeof(TypeId) / 3) + 3;
    char s[len];
    snprintf(s, len, "%zd", t);
    Type<String>::Cptr p = String::create(s);
    return p;
}

static Type<String>::Cptr objectToString(const Value& val) {
    Type<Object>::Cptr o = toCptr<Object>(val);
    if (o)
        return o->toString();
    else {
        LIBJ_NULL_CPTR(String, nullp);
        return nullp;
    }
}

Type<String>::Cptr String::valueOf(const Value& val) {
    if (val.empty()) {
        LIBJ_NULL_CPTR(String, nullp);
        return nullp;
    } else if (val.type() == Type<Boolean>::id()) {
        return booleanToString(val);
    } else if (val.type() == Type<Byte>::id()) {
        return byteToString(val);
    } else if (val.type() == Type<Short>::id()) {
        return shortToString(val);
    } else if (val.type() == Type<Int>::id()) {
        return intToString(val);
    } else if (val.type() == Type<Long>::id()) {
        return longToString(val);
    } else if (val.type() == Type<Float>::id()) {
        return floatToString(val);
    } else if (val.type() == Type<Double>::id()) {
        return doubleToString(val);
    } else if (val.type() == Type<Size>::id()) {
        return sizeToString(val);
    } else if (val.type() == Type<TypeId>::id()) {
        return typeIdToString(val);
    } else if (val.instanceOf(Type<Object>::id())) {
        return objectToString(val);
    } else {
        LIBJ_NULL_CPTR(String, nullp);
        return nullp;
    }
}

}  // namespace libj
