// Copyright (c) 2012 Plenluno All rights reserved.

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

std::string fromUtf32(const std::u32string& str, UnicodeEncoding enc);
std::u32string toUtf32(const void* data, UnicodeEncoding enc, size_t max);

std::u32string utf16ToUtf32(const std::u16string& str);
std::u16string utf32ToUtf16(const std::u32string& str);

}  // namespace glue
}  // namespace libj

#endif  // LIBJ_GLUE_CVTUTF_H_
