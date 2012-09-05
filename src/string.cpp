// Copyright (c) 2012 Plenluno All rights reserved.

#include <stdio.h>
#include <iv/lv5/third_party/v8_dtoa/conversions.h>

#include "./string_impl.h"

namespace libj {

String::CPtr String::create() {
    static const String::CPtr empty =
        StringImpl::create(NULL, UTF8, NO_POS);
    return empty;
}

String::CPtr String::create(Char c, Size n) {
    return StringImpl::create(c, n);
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

static String::CPtr shortToString(const Value& val) {
    Short sh;
    to<Short>(val, &sh);
    const Size kLen = (16 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", sh);
    return String::create(s);
}

static String::CPtr intToString(const Value& val) {
    Int i;
    to<Int>(val, &i);
    const Size kLen = (32 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%d", i);
    String::CPtr p = String::create(s);
    return p;
}

static String::CPtr longToString(const Value& val) {
    Long l;
    to<Long>(val, &l);
    const Size kLen = (64 / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%lld", l);
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
    String::CPtr p = String::create(s);
    return p;
}

static String::CPtr typeIdToString(const Value& val) {
    TypeId t;
    to<TypeId>(val, &t);
    const Size kLen = ((sizeof(TypeId) << 3) / 3) + 3;
    char s[kLen];
    snprintf(s, kLen, "%zd", t);
    String::CPtr p = String::create(s);
    return p;
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
    } else if (val.instanceof(Type<Object>::id())) {
        return objectToString(val);
    } else {
        return null();
    }
}

}  // namespace libj
