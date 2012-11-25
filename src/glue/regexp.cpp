// Copyright (c) 2012 Plenluno All rights reserved.

#include <assert.h>
#include <iv/aero/aero.h>
#include <string>
#include <vector>

#include "libj/glue/regexp.h"

namespace libj {
namespace glue {

typedef std::basic_string<uint16_t> U16String;

static U16String toU16String(String::CPtr str) {
#ifdef LIBJ_USE_CXX11
    U16String s;
    std::u16string ss = str->toStdU16String();
    for (size_t i = 0; i < ss.length(); i++) {
        s.push_back(ss[i]);
    }
    return s;
#else
    return str->toStdU16String();
#endif
}

class RegExpImpl : public RegExp {
 public:
    virtual Boolean global() const {
        return flags_ & JsRegExp::GLOBAL;
    }

    virtual Boolean ignoreCase() const {
        return flags_ & JsRegExp::IGNORE_CASE;
    }

    virtual Boolean multiline() const {
        return flags_ & JsRegExp::MULTILINE;
    }

    virtual Boolean execute(
        String::CPtr str,
        int offset,
        std::vector<int>& captures) const {
        if (!str) return false;

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

    Boolean valid() {
        return !!code_;
    }

    RegExpImpl(const U16String& pattern, UInt flags)
        : flags_(flags)
        , code_(NULL) {
        iv::core::Space space;
        int fs = (flags & JsRegExp::IGNORE_CASE ? iv::aero::IGNORE_CASE : 0)
               | (flags & JsRegExp::MULTILINE ? iv::aero::MULTILINE : 0);
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
    UInt flags_;
    iv::aero::Code* code_;
};

RegExp* RegExp::create(String::CPtr pattern, UInt flags) {
    if (!pattern) return NULL;

    U16String ptn = toU16String(pattern);
    RegExpImpl* re = new RegExpImpl(ptn, flags);
    if (re->valid()) {
        return re;
    } else {
        delete re;
        return NULL;
    }
}

}  // namespace glue
}  // namespace libj
