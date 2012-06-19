// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_STRING_H_
#define LIBJ_STRING_H_

#include <string>

#include "libj/immutable.h"
#include "libj/value.h"

#ifndef LIBJ_USE_CXX11
namespace std {

typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

}  // namespace std
#endif

namespace libj {

extern const Size NO_POS;
extern const Char NO_CHAR;

class String : LIBJ_IMMUTABLE(String)
 public:
    enum Encoding {
        ASCII,
        UTF8,
        UTF16,
        UTF32,
    };

    static CPtr create(const void* = 0, Encoding = ASCII, Size = NO_POS);
    static CPtr valueOf(const Value&);

    virtual Size length() const = 0;
    virtual Char charAt(Size) const = 0;
    virtual CPtr concat(CPtr) const = 0;
    virtual CPtr substring(Size) const = 0;
    virtual CPtr substring(Size, Size) const = 0;
    virtual Size indexOf(Char, Size = 0) const = 0;
    virtual Size indexOf(CPtr, Size = 0) const = 0;
    virtual Size lastIndexOf(Char, Size = NO_POS) const = 0;
    virtual Size lastIndexOf(CPtr, Size = NO_POS) const = 0;
    virtual Boolean isEmpty() const = 0;
    virtual Boolean isAscii() const = 0;
    virtual Boolean startsWith(CPtr, Size = 0) const = 0;
    virtual Boolean endsWith(CPtr) const = 0;
    virtual CPtr toLowerCase() const = 0;
    virtual CPtr toUpperCase() const = 0;
    virtual std::string toStdString() const = 0;
#if 0
    // TODO(plenluno): implement
    virtual std::u16string toU16String() const = 0;
    virtual std::u32string toU32String() const = 0;
#endif
};

}  // namespace libj

#endif  // LIBJ_STRING_H_
