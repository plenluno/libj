// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_GLUE_REGEXP_H_
#define LIBJ_GLUE_REGEXP_H_

#include <string>
#include <vector>

namespace libj {
namespace glue {

class RegExp {
 public:
    enum Flag {
        GLOBAL      = 1 << 0,
        IGNORE_CASE = 1 << 1,
        MULTILINE   = 1 << 2,
    };

    enum Encoding {
        UTF8,
        UTF16,
        UTF32
    };

    static RegExp* create(const std::string& pattern, unsigned flags);

    static Encoding encoding();

    virtual ~RegExp() {}

    virtual bool global() const = 0;

    virtual bool ignoreCase() const = 0;

    virtual bool multiline() const = 0;

    virtual bool execute(
        const std::string& str,
        int offset,
        std::vector<int>& captures) const = 0;
};

}  // namespace glue
}  // namespace libj

#endif  // LIBJ_GLUE_REGEXP_H_
