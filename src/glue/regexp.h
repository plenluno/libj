// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef SRC_GLUE_REGEXP_H_
#define SRC_GLUE_REGEXP_H_

#include <vector>
#include <assert.h>
#include <libj/typedef.h>

namespace libj {
namespace glue {

class RegExp {
 public:
    enum Flag {
        IGNORE_CASE = 1 << 1,
        MULTILINE   = 1 << 2,
    };

    static RegExp* create(const std::u16string& pattern, unsigned int flags);

    bool ignoreCase() const;
    bool multiline() const;

    int execute(
        const std::u16string& str,
        int offset,
        std::vector<int>& captures) const;

 private:
    std::u16string pattern_;
    int flags_;
    void* code_;

    RegExp(const std::u16string& pattern, int flags)
        : pattern_(pattern)
        , flags_(flags)
        , code_(NULL) {}

 public:
     virtual ~RegExp();
};

}  // namespace glue
}  // namespace libj

#endif  // SRC_GLUE_REGEXP_H_
