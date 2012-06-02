// Copyright (c) 2012 Plenluno All rights reserved.

#include <string>

#include "./string_impl.h"
#include "cvtutf/ConvertUTF.h"

namespace cvtutf {

typedef libj::Size Size;
typedef libj::StringImpl::Str8 Str8;
typedef libj::StringImpl::Str32 Str32;

const int kConvertBufferSize = 32;
const ConversionFlags kConvertFlag = lenientConversion;

template<typename T>
ConversionResult convertToUtf32(
    const T**, Size*, UTF32**, UTF32*, ConversionFlags);

template<>
ConversionResult convertToUtf32(
    const UTF8** sourceStart, Size* nChar,
    UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
    return nConvertUTF8toUTF32(
        sourceStart, nChar, targetStart, targetEnd, flags);
}

template<>
ConversionResult convertToUtf32(
    const UTF16** sourceStart, Size* nChar,
    UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
    return nConvertUTF16toUTF32(
        sourceStart, nChar, targetStart, targetEnd, flags);
}

template<typename T>
Str32* convertToUtf32(const T* src, Size max) {
    UTF32 buf[kConvertBufferSize];
    Str32* dst = new Str32();
    UTF32* end32 = buf + kConvertBufferSize;
    ConversionResult r;
    do {
        UTF32* cur32 = buf;
        r = convertToUtf32<T>(&src, &max, &cur32, end32, kConvertFlag);
        dst->append(reinterpret_cast<libj::Char*>(buf), cur32 - buf);
    } while (r == targetExhausted);
    return dst;
}

Str8 convertStr32ToStr8(const Str32* str32) {
    UTF8 buf[kConvertBufferSize];
    const UTF32* cur32 = reinterpret_cast<const UTF32*>(str32->c_str());
    const UTF32* end32 = cur32 + str32->length();
    UTF8* end8 = buf + kConvertBufferSize;
    Str8 dst = Str8();
    ConversionResult r;
    do {
        UTF8* cur8 = buf;
        r = ConvertUTF32toUTF8(&cur32, end32, &cur8, end8, kConvertFlag);
        dst.append(reinterpret_cast<char*>(buf), cur8 - buf);
    } while (r == targetExhausted);
    return dst;
}

}  // namespace cvtutf

namespace libj {

String::CPtr StringImpl::create(const void* data, Encoding enc, Size max) {
    if (enc == ASCII) {
        CPtr p(new StringImpl(static_cast<const char*>(data), max));
        return p;
    } else if (enc == UTF8) {
        Str32* s = cvtutf::convertToUtf32<cvtutf::UTF8>(
            static_cast<const cvtutf::UTF8*>(data), max);
        CPtr p(new StringImpl(0, s));
        return p;
    } else if (enc == UTF16) {
        Str32* s = cvtutf::convertToUtf32<cvtutf::UTF16>(
            static_cast<const cvtutf::UTF16*>(data), max);
        CPtr p(new StringImpl(0, s));
        return p;
    } else if (enc == UTF32) {
        CPtr p(new StringImpl(static_cast<const Char*>(data), max));
        return p;
    } else {
        LIBJ_NULL_CPTR(String, nullp);
        return nullp;
    }
}

std::string StringImpl::toStdString() const {
    if (isAscii()) {
        return str8_ ? *str8_ : std::string();
    } else {
        return cvtutf::convertStr32ToStr8(str32_);
    }
}

}  // namespace libj
