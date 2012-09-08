// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef SRC_GLUE_REGEXP_H_
#define SRC_GLUE_REGEXP_H_

#include <string>
#include <vector>

namespace libj {
namespace glue {

class RegExp {
 public:
    typedef std::basic_string<uint16_t> U16String;

    enum Flag {
        NONE        = 0,
        GLOBAL      = 1 << 0,
        IGNORE_CASE = 1 << 1,
        MULTILINE   = 1 << 2,
    };

    static RegExp* create(const U16String& pattern, unsigned int flags);

    bool global() const;
    bool ignoreCase() const;
    bool multiline() const;

    bool execute(
        const U16String& str,
        int offset,
        std::vector<int>& captures) const;

 private:
    U16String pattern_;
    unsigned int flags_;
    void* code_;

    RegExp(const U16String& pattern, int flags)
        : pattern_(pattern)
        , flags_(flags)
        , code_(NULL) {}

 public:
     virtual ~RegExp();
};

}  // namespace glue
}  // namespace libj

#endif  // SRC_GLUE_REGEXP_H_
