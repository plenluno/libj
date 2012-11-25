// Copyright (c) 2012 Plenluno All rights reserved.

#include <iv/aero/aero.h>
#include <string>
#include <vector>

#include "libj/glue/regexp.h"

namespace libj {
namespace glue {

typedef std::basic_string<uint16_t> U16String;

static U16String toU16String(const std::string& str) {
    return U16String(reinterpret_cast<const uint16_t*>(str.c_str()));
}

class RegExpImpl : public RegExp {
 public:
    virtual bool global() const {
        return flags_ & GLOBAL;
    }

    virtual bool ignoreCase() const {
        return flags_ & IGNORE_CASE;
    }

    virtual bool multiline() const {
        return flags_ & MULTILINE;
    }

    virtual bool execute(
        const std::string& str,
        int offset,
        std::vector<int>& captures) const {
        static iv::aero::VM vm;
        captures.clear();
        assert(code_);
        size_t n = code_->captures() * 2;
        for (size_t i = 0; i < n; i++) {
            captures.push_back(-1);
        }
        int res = vm.Execute(code_, toU16String(str), captures.data(), offset);
        return res == iv::aero::AERO_SUCCESS;
    }

    bool valid() const {
        return !!code_;
    }

    RegExpImpl(const U16String& pattern, unsigned flags)
        : flags_(flags)
        , code_(NULL) {
        iv::core::Space space;
        int fs = (flags & IGNORE_CASE ? iv::aero::IGNORE_CASE : 0)
               | (flags & MULTILINE ? iv::aero::MULTILINE : 0);
        int error = 0;
        code_ = iv::aero::Compile(&space, pattern, fs, &error);
        if (error) {
            flags_ = 0;
            delete code_;
            code_ = NULL;
        }
    }

    virtual ~RegExpImpl() {
        delete code_;
    }

 private:
    unsigned flags_;
    iv::aero::Code* code_;
};

RegExp* RegExp::create(const std::string& pattern, unsigned flags) {
    U16String ptn = toU16String(pattern);
    RegExpImpl* re = new RegExpImpl(ptn, flags);
    if (re->valid()) {
        return re;
    } else {
        delete re;
        return NULL;
    }
}

RegExp::Encoding RegExp::encoding() {
    return UTF16;
}

}  // namespace glue
}  // namespace libj
