// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_STRING_BUILDER_H_
#define LIBJ_STRING_BUILDER_H_

#include <libj/mutable.h>
#include <libj/string.h>

namespace libj {

class StringBuilder : LIBJ_MUTABLE(StringBuilder)
 public:
    static Ptr create();

    virtual Size length() const = 0;

    virtual Char charAt(Size index) const = 0;

    virtual Ptr append(const Value& val) = 0;

    virtual Ptr appendChar(Char c) = 0;

    virtual Ptr appendCStr(const char* cstr) = 0;

    virtual Boolean setCharAt(Size index, Char c) = 0;
};

}  // namespace libj

#endif  // LIBJ_STRING_BUILDER_H_
