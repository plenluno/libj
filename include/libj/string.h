// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_STRING_H_
#define LIBJ_STRING_H_

#include <libj/constant.h>
#include <libj/immutable.h>
#include <libj/value.h>

#include <stdio.h>
#include <string>

namespace libj {

class String : LIBJ_IMMUTABLE(String)
 public:
    enum Encoding {
        UTF8,
        UTF16BE,
        UTF16LE,
        UTF32BE,
        UTF32LE,
    };

    static CPtr create();

    static CPtr create(Char c, Size n = 1);

    static CPtr create(const std::u16string& s16);

    static CPtr create(const std::u32string& s32);

    static CPtr create(
        const void* data,
        Encoding enc = UTF8,
        Size len = NO_SIZE,
        Size max = NO_SIZE);

    static CPtr intern(CPtr str);

    static CPtr intern(
        const void* data,
        Encoding enc = UTF8,
        Size len = NO_SIZE,
        Size max = NO_SIZE);

    static CPtr valueOf(const Value& val);

    virtual Size length() const = 0;

    virtual Char charAt(Size index) const = 0;

    virtual CPtr concat(CPtr str) const = 0;

    virtual CPtr substring(Size from) const = 0;

    virtual CPtr substring(Size from, Size to) const = 0;

    virtual Size indexOf(Char c, Size from = 0) const = 0;

    virtual Size indexOf(CPtr str, Size from = 0) const = 0;

    virtual Size lastIndexOf(Char c, Size from = NO_POS) const = 0;

    virtual Size lastIndexOf(CPtr str, Size from = NO_POS) const = 0;

    virtual Boolean isEmpty() const = 0;

    virtual Boolean isInterned() const = 0;

    virtual Boolean startsWith(CPtr str, Size from = 0) const = 0;

    virtual Boolean endsWith(CPtr str) const = 0;

    virtual CPtr toLowerCase() const = 0;

    virtual CPtr toUpperCase() const = 0;

    virtual const Char* data() const = 0;

    virtual std::string toStdString(Encoding enc = UTF8) const = 0;

    virtual std::u16string toStdU16String() const = 0;

    virtual std::u32string toStdU32String() const = 0;
};

}  // namespace libj

#ifdef LIBJ_DEBUG
# define LIBJ_STATIC_CONST_STRING_DEF(N, V) \
    static const libj::String::CPtr N = libj::String::intern(V);
#else
# define LIBJ_STATIC_CONST_STRING_DEF(N, V) \
    static const libj::String::CPtr N = libj::String::create(V);
#endif

#endif  // LIBJ_STRING_H_
