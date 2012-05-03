// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_STRING_H_
#define LIBJ_STRING_H_

#include "libj/immutable.h"

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

    static Cptr create(const void*, Encoding = ASCII, Size = NO_POS);

    virtual Size length() const = 0;
    virtual Char charAt(Size) const = 0;
    virtual Cptr substring(Size) const = 0;
    virtual Cptr substring(Size, Size) const = 0;
    virtual Cptr concat(Cptr) const = 0;
    virtual bool startsWith(Cptr, Size = 0) const = 0;
    virtual bool endsWith(Cptr) const = 0;
    virtual Size indexOf(Char, Size = 0) const = 0;
    virtual Size indexOf(Cptr, Size = 0) const = 0;
    virtual Size lastIndexOf(Char, Size = NO_POS) const = 0;
    virtual Size lastIndexOf(Cptr, Size = NO_POS) const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isAscii() const = 0;
};

}  // namespace libj

#endif  // LIBJ_STRING_H_
