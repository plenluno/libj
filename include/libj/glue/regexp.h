// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_GLUE_REGEXP_H_
#define LIBJ_GLUE_REGEXP_H_

#include <vector>

#include "libj/js_regexp.h"
#include "libj/string.h"

namespace libj {
namespace glue {

class RegExp {
 public:
    // see JsRegExp::Flag
    static RegExp* create(String::CPtr pattern, UInt flags);

    virtual ~RegExp() {}

    virtual Boolean global() const = 0;

    virtual Boolean ignoreCase() const = 0;

    virtual Boolean multiline() const = 0;

    virtual Boolean execute(
        String::CPtr str,
        int offset,
        std::vector<int>& captures) const = 0;
};

}  // namespace glue
}  // namespace libj

#endif  // LIBJ_GLUE_REGEXP_H_
