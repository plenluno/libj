// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_UTIL_H_
#define LIBJ_DETAIL_UTIL_H_

#include <libj/exception.h>
#include <libj/value.h>
#include <libj/glue/dtoa.h>

#ifdef LIBJ_PF_WINDOWS
    #include <libj/platform/windows.h>
#endif

namespace libj {
namespace detail {

template<typename T>
inline Boolean convert(const Value& v, T* t, Boolean throwable = true) {
    Boolean result = to<T>(v, t);
#ifdef LIBJ_USE_EXCEPTION
    if (!result && throwable) LIBJ_THROW(Error::ILLEGAL_TYPE);
#endif  // LIBJ_USE_EXCEPTION
    return result;
}

inline void booleanToString(const Value& val, char* buf, Size len) {
    if (len < 6) return;

    Boolean b;
    to<Boolean>(val, &b);
    if (b) {
        // true
        buf[0] = 't';
        buf[1] = 'r';
        buf[2] = 'u';
        buf[3] = 'e';
        buf[4] = 0;
    } else {
        // false
        buf[0] = 'f';
        buf[1] = 'a';
        buf[2] = 'l';
        buf[3] = 's';
        buf[4] = 'e';
        buf[5] = 0;
    }
}

inline void byteToString(const Value& val, char* buf, Size len) {
    Byte b;
    to<Byte>(val, &b);
    snprintf(buf, len, "%d", b);
}

inline void ubyteToString(const Value& val, char* buf, Size len) {
    UByte ub;
    to<UByte>(val, &ub);
    snprintf(buf, len, "%d", ub);
}

inline void shortToString(const Value& val, char* buf, Size len) {
    Short sh;
    to<Short>(val, &sh);
    snprintf(buf, len, "%d", sh);
}

inline void ushortToString(const Value& val, char* buf, Size len) {
    UShort ush;
    to<UShort>(val, &ush);
    snprintf(buf, len, "%d", ush);
}

inline void intToString(const Value& val, char* buf, Size len) {
    Int i;
    to<Int>(val, &i);
    snprintf(buf, len, "%d", i);
}

inline void uintToString(const Value& val, char* buf, Size len) {
    UInt ui;
    to<UInt>(val, &ui);
    snprintf(buf, len, "%d", ui);
}

inline void longToString(const Value& val, char* buf, Size len) {
    Long l;
    to<Long>(val, &l);
    snprintf(buf, len, "%lld", l);
}

inline void ulongToString(const Value& val, char* buf, Size len) {
    ULong ul;
    to<ULong>(val, &ul);
    snprintf(buf, len, "%lld", ul);
}

inline void sizeToString(const Value& val, char* buf, Size len) {
    Size n;
    to<Size>(val, &n);
    snprintf(buf, len, "%zd", n);
}

inline void typeidToString(const Value& val, char* buf, Size len) {
    TypeId t;
    to<TypeId>(val, &t);
    snprintf(buf, len, "%zd", t);
}

inline void floatToString(const Value& val, char* buf, Size len) {
    Float f;
    to<Float>(val, &f);
    glue::dtoa::doubleToString(f, buf, len);
}

inline void doubleToString(const Value& val, char* buf, Size len) {
    Double d;
    to<Double>(val, &d);
    glue::dtoa::doubleToString(d, buf, len);
}

inline Boolean primitiveToString(const Value& val, char* buf, Size len) {
    if (val.type() == Type<Boolean>::id()) {
        booleanToString(val, buf, len);
    } else if (val.type() == Type<Byte>::id()) {
        byteToString(val, buf, len);
    } else if (val.type() == Type<UByte>::id()) {
        ubyteToString(val, buf, len);
    } else if (val.type() == Type<Short>::id()) {
        shortToString(val, buf, len);
    } else if (val.type() == Type<UShort>::id()) {
        ushortToString(val, buf, len);
    } else if (val.type() == Type<Int>::id()) {
        intToString(val, buf, len);
    } else if (val.type() == Type<UInt>::id()) {
        uintToString(val, buf, len);
    } else if (val.type() == Type<Long>::id()) {
        longToString(val, buf, len);
    } else if (val.type() == Type<ULong>::id()) {
        ulongToString(val, buf, len);
    } else if (val.type() == Type<Float>::id()) {
        floatToString(val, buf, len);
    } else if (val.type() == Type<Double>::id()) {
        doubleToString(val, buf, len);
    } else if (val.type() == Type<Size>::id()) {
        sizeToString(val, buf, len);
    } else if (val.type() == Type<TypeId>::id()) {
        typeidToString(val, buf, len);
    } else {
        return false;
    }
    return true;
}

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_UTIL_H_
