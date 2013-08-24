// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_TO_STRING_H_
#define LIBJ_DETAIL_TO_STRING_H_

#include <libj/value.h>
#include <libj/glue/dtoa.h>

#include <assert.h>

namespace libj {
namespace detail {

template<typename T>
inline const Char* signedToString(const Value& val, Char* buf, Size len) {
    T t = to<T>(val);

    Boolean sign = t < 0;
    if (sign) t = -t;

    Char* cp = buf + len - 1;
    *cp-- = 0;

    T radix = 10;
    do {
        *cp-- = '0' + t % radix;
        t /= radix;
    } while (t > 0);

    if (sign) {
        *cp = '-';
        return cp;
    } else {
        return cp + 1;
    }
}

template<typename T>
inline const Char* unsignedToString(const Value& val, Char* buf, Size len) {
    T t = to<T>(val);

    Char* cp = buf + len - 1;
    *cp-- = 0;

    T radix = 10;
    do {
        *cp-- = '0' + t % radix;
        t /= radix;
    } while (t > 0);

    return cp + 1;
}

inline const Char* integerToString(const Value& val, Char* buf, Size len) {
    if (val.is<Int>()) {
        return signedToString<Int>(val, buf, len);
    } else if (val.is<Long>()) {
        return signedToString<Long>(val, buf, len);
    } else if (val.is<Size>()) {
        return unsignedToString<Size>(val, buf, len);
    } else if (val.is<UInt>()) {
        return unsignedToString<UInt>(val, buf, len);
    } else if (val.is<ULong>()) {
        return unsignedToString<ULong>(val, buf, len);
    } else if (val.is<Byte>()) {
        return signedToString<Byte>(val, buf, len);
    } else if (val.is<UByte>()) {
        return unsignedToString<UByte>(val, buf, len);
    } else if (val.is<Short>()) {
        return signedToString<Short>(val, buf, len);
    } else if (val.is<UShort>()) {
        return unsignedToString<UShort>(val, buf, len);
    } else if (val.is<TypeId>()) {
        return unsignedToString<TypeId>(val, buf, len);
    } else {
        assert(false);
        return NULL;
    }
}

inline String::CPtr integerToString(const Value& val) {
    const Size kLen = 64;
    Char buf[kLen];
#ifdef LIBJ_USE_UTF32
    return String::create(integerToString(val, buf, kLen), String::UTF32);
#else
    return String::create(integerToString(val, buf, kLen), String::UTF16);
#endif
}

inline void floatToString(const Value& val, char* buf, Size len) {
    Float f = to<Float>(val);
    glue::dtoa::doubleToString(f, buf, len);
}

inline String::CPtr floatToString(const Value& val) {
    const Size kLen = 64;
    char buf[kLen];
    floatToString(val, buf, kLen);
    return String::create(buf);
}

inline void doubleToString(const Value& val, char* buf, Size len) {
    Double d = to<Double>(val);
    glue::dtoa::doubleToString(d, buf, len);
}

inline String::CPtr doubleToString(const Value& val) {
    const Size kLen = 64;
    char buf[kLen];
    doubleToString(val, buf, kLen);
    return String::create(buf);
}

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_TO_STRING_H_
