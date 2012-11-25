// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/js_regexp.h"
#include "libj/detail/js_regexp.h"

namespace libj {

JsRegExp::Ptr JsRegExp::create(String::CPtr pattern, UInt flags) {
    if (!pattern) return null();

    detail::JsRegExp<JsRegExp>* re =
        new detail::JsRegExp<JsRegExp>(pattern, flags);
    if (re->valid()) {
        return Ptr(re);
    } else {
        delete re;
        return null();
    }
}

}  // namespace libj
