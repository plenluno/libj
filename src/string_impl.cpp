// Copyright (c) 2012 Plenluno All rights reserved.

#include <string>

#include "./string_impl.h"
#include "cvtutf/ConvertUTF.h"

namespace cvtutf {

typedef libj::Size Size;
typedef std::basic_string<char> Str8;
typedef std::basic_string<libj::Char16> Str16;
typedef std::basic_string<libj::Char32> Str32;

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
        dst->append(reinterpret_cast<libj::Char32*>(buf), cur32 - buf);
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

Str16 convertStr32ToStr16(const Str32* str32) {
    UTF16 buf[kConvertBufferSize];
    const UTF32* cur32 = reinterpret_cast<const UTF32*>(str32->c_str());
    const UTF32* end32 = cur32 + str32->length();
    UTF16* end16 = buf + kConvertBufferSize;
    Str16 dst = Str16();
    ConversionResult r;
    do {
        UTF16* cur16 = buf;
        r = ConvertUTF32toUTF16(&cur32, end32, &cur16, end16, kConvertFlag);
        dst.append(reinterpret_cast<libj::Char16*>(buf), cur16 - buf);
    } while (r == targetExhausted);
    return dst;
}

}  // namespace cvtutf

namespace libj {

String::CPtr StringImpl::create(Char c, Size n) {
    CPtr p(new StringImpl(c, n));
    return p;
}

String::CPtr StringImpl::create(const void* data, Encoding enc, Size max) {
    if (!data) {
        CPtr p(new StringImpl());
        return p;
    }

    if (enc == UTF8) {
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
        return null();
    }
}

std::string StringImpl::toStdString() const {
    if (isAscii()) {
        return str8_ ? *str8_ : std::string();
    } else {
        return cvtutf::convertStr32ToStr8(str32_);
    }
}

std::u16string StringImpl::toStdU16String() const {
    if (isAscii()) {
        std::u16string s16;
        if (str8_) {
            Size len = str8_->length();
            for (Size i = 0; i < len; i++) {
                s16.push_back((*str8_)[i]);
            }
        }
        return s16;
    } else {
        return cvtutf::convertStr32ToStr16(str32_);
    }
}

std::u32string StringImpl::toStdU32String() const {
    if (isAscii()) {
        std::u32string s32;
        if (str8_) {
            Size len = str8_->length();
            for (Size i = 0; i < len; i++) {
                s32.push_back((*str8_)[i]);
            }
        }
        return s32;
    } else {
        return str32_ ? *str32_ : std::u32string();
    }
}

}  // namespace libj
