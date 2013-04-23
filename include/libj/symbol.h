// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_SYMBOL_H_
#define LIBJ_SYMBOL_H_

#include <libj/string.h>

namespace libj {

struct Symbol {
    typedef const String::CPtr CPtr;

    static CPtr create(const char* str);

    static CPtr create(String::CPtr str);
};

}  // namespace libj

#define LIBJ_SYMBOL_DEF(N, V) \
    libj::Symbol::CPtr N = libj::String::intern(V);

#define LIBJ_STATIC_SYMBOL_DEF(N, V) \
    static libj::Symbol::CPtr N = libj::String::intern(V);

#endif  // LIBJ_SYMBOL_H_
