// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/string.h>
#include <libj/symbol.h>
#include <libj/glue/dtoa.h>
#include <libj/detail/string.h>

#ifdef LIBJ_PF_WINDOWS
    #include <libj/platform/windows.h>
#endif

namespace libj {

String::CPtr String::create() {
    static const CPtr empty(intern(CPtr(new detail::String())));
    return empty;
}

String::CPtr String::create(Char c, Size n) {
    return CPtr(new detail::String(c, n));
}

String::CPtr String::create(const std::u16string& s16) {
    return CPtr(new detail::String(s16));
}

String::CPtr String::create(const std::u32string& s32) {
    return CPtr(new detail::String(s32));
}

String::CPtr String::create(const void* data, Encoding enc, Size max) {
    if (data) {
        return CPtr(new detail::String(data, enc, max));
    } else {
        return null();
    }
}

String::CPtr String::intern(String::CPtr str) {
    return detail::String::intern(str);
}

String::CPtr String::intern(const void* data, Encoding enc, Size max) {
    return intern(String::create(data, enc, max));
}

static String::CPtr booleanToString(const Value& val) {
    LIBJ_STATIC_SYMBOL_DEF(symTrue, "true");
    LIBJ_STATIC_SYMBOL_DEF(symFalse, "false");

    Boolean b;
    to<Boolean>(val, &b);
    return b ? symTrue : symFalse;
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

static String::CPtr floatToString(const Value& val) {
    Float f;
    to<Float>(val, &f);
    return glue::dtoa::doubleToString(f);
}

static String::CPtr doubleToString(const Value& val) {
    Double d;
    to<Double>(val, &d);
    return glue::dtoa::doubleToString(d);
}

static String::CPtr objectToString(const Value& val) {
    LIBJ_STATIC_SYMBOL_DEF(symNull, "null");

    String::CPtr s = toCPtr<String>(val);
    if (s) return s;

    Object::CPtr o = toCPtr<Object>(val);
    if (o) {
        return o->toString();
    } else {
        return symNull;
    }
}

String::CPtr String::valueOf(const Value& val) {
    LIBJ_STATIC_SYMBOL_DEF(symUndefined, "undefined");

    if (val.isUndefined()) {
        return symUndefined;
    } else if (val.isPtr() || val.isCPtr()) {
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
