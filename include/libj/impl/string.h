// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_IMPL_STRING_H_
#define LIBJ_IMPL_STRING_H_

namespace libj {

inline String::CPtr str(const char* utf8) {
    return String::create(utf8, String::UTF8);
}

inline String::CPtr str(const char16_t* utf16) {
    return String::create(utf16, String::UTF16);
}

inline String::CPtr str(const char32_t* utf32) {
    return String::create(utf32, String::UTF32);
}

}  // namespace libj

#endif  // LIBJ_IMPL_STRING_H_
