// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_GLUE_CVTUTF_H_
#define LIBJ_GLUE_CVTUTF_H_

#include <libj/typedef.h>

#include <string>

namespace libj {
namespace glue {

enum UnicodeEncoding {
    UTF8,
    UTF16BE,
    UTF16LE,
    UTF32BE,
    UTF32LE,
};

size_t byteLengthAt(
    const void* data,
    UnicodeEncoding enc);

char32_t codePointAt(
    const void* data,
    UnicodeEncoding enc);

std::string fromUtf8(
    const std::string& str,
    UnicodeEncoding enc);

std::string fromUtf16(
    const std::u16string& str,
    UnicodeEncoding enc);

std::string fromUtf32(
    const std::u32string& str,
    UnicodeEncoding enc);

std::string toUtf8(
    const void* data,
    UnicodeEncoding enc,
    size_t len,
    size_t max);

std::u16string toUtf16(
    const void* data,
    UnicodeEncoding enc,
    size_t len,
    size_t max);

std::u32string toUtf32(
    const void* data,
    UnicodeEncoding enc,
    size_t len,
    size_t max);

std::string utf16ToUtf8(const std::u16string& str);

std::u16string utf8ToUtf16(const std::string& str);

std::u32string utf16ToUtf32(const std::u16string& str);

std::u16string utf32ToUtf16(const std::u32string& str);

}  // namespace glue
}  // namespace libj

#endif  // LIBJ_GLUE_CVTUTF_H_
