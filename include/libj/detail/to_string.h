// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_TO_STRING_H_
#define LIBJ_DETAIL_TO_STRING_H_

#include <libj/value.h>
#include <libj/glue/dtoa.h>

#ifdef LIBJ_PF_WINDOWS
#include <libj/platform/windows.h>
#endif

#include <assert.h>

namespace libj {
namespace detail {

inline void byteToString(const Value& val, char* buf, Size len) {
    Byte b = to<Byte>(val);
    snprintf(buf, len, "%d", b);
}

inline void ubyteToString(const Value& val, char* buf, Size len) {
    UByte ub = to<UByte>(val);
    snprintf(buf, len, "%d", ub);
}

inline void shortToString(const Value& val, char* buf, Size len) {
    Short sh = to<Short>(val);
    snprintf(buf, len, "%d", sh);
}

inline void ushortToString(const Value& val, char* buf, Size len) {
    UShort ush = to<UShort>(val);
    snprintf(buf, len, "%d", ush);
}

inline void intToString(const Value& val, char* buf, Size len) {
    Int i = to<Int>(val);
    snprintf(buf, len, "%d", i);
}

inline void uintToString(const Value& val, char* buf, Size len) {
    UInt ui = to<UInt>(val);
    snprintf(buf, len, "%d", ui);
}

inline void longToString(const Value& val, char* buf, Size len) {
    Long l = to<Long>(val);
    snprintf(buf, len, "%lld", static_cast<long long>(l));
}

inline void ulongToString(const Value& val, char* buf, Size len) {
    ULong ul = to<ULong>(val);
    snprintf(buf, len, "%llu", static_cast<unsigned long long>(ul));
}

inline void sizeToString(const Value& val, char* buf, Size len) {
    Size n = to<Size>(val);
    snprintf(buf, len, "%zd", n);
}

inline void typeidToString(const Value& val, char* buf, Size len) {
    TypeId t = to<TypeId>(val);
    snprintf(buf, len, "%zd", t);
}

inline void floatToString(const Value& val, char* buf, Size len) {
    Float f = to<Float>(val);
    glue::dtoa::doubleToString(f, buf, len);
}

inline void doubleToString(const Value& val, char* buf, Size len) {
    Double d = to<Double>(val);
    glue::dtoa::doubleToString(d, buf, len);
}

inline Boolean primitiveToString(const Value& val, char* buf, Size len) {
    assert(!val.is<Boolean>());
    if (val.is<Byte>()) {
        byteToString(val, buf, len);
    } else if (val.is<UByte>()) {
        ubyteToString(val, buf, len);
    } else if (val.is<Short>()) {
        shortToString(val, buf, len);
    } else if (val.is<UShort>()) {
        ushortToString(val, buf, len);
    } else if (val.is<Int>()) {
        intToString(val, buf, len);
    } else if (val.is<UInt>()) {
        uintToString(val, buf, len);
    } else if (val.is<Long>()) {
        longToString(val, buf, len);
    } else if (val.is<ULong>()) {
        ulongToString(val, buf, len);
    } else if (val.is<Float>()) {
        floatToString(val, buf, len);
    } else if (val.is<Double>()) {
        doubleToString(val, buf, len);
    } else if (val.is<Size>()) {
        sizeToString(val, buf, len);
    } else if (val.is<TypeId>()) {
        typeidToString(val, buf, len);
    } else {
        return false;
    }
    return true;
}

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_TO_STRING_H_
