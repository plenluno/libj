// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_REGEXP_H_
#define LIBJ_JS_REGEXP_H_

#include "libj/js_array.h"
#include "libj/js_object.h"
#include "libj/string.h"

namespace libj {

class JsRegExp : LIBJ_JS_OBJECT(JsRegExp)
 public:
    enum Flag {
        NONE        = 0,
        GLOBAL      = 1 << 0,
        IGNORE_CASE = 1 << 1,
        MULTILINE   = 1 << 2,
    };

    static Ptr create(String::CPtr pattern, UInt flags = NONE);

    virtual Boolean global() const = 0;
    virtual Boolean ignoreCase() const = 0;
    virtual Boolean multiline() const = 0;
    virtual String::CPtr source() const =0;

    virtual JsArray::Ptr exec(String::CPtr str) const = 0;
    virtual Boolean test(String::CPtr str) const = 0;
};

}  // namespace libj

#endif  // LIBJ_JS_REGEXP_H_
