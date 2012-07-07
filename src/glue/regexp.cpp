// Copyright (c) 2012 Plenluno All rights reserved.

#include <iv/aero/aero.h>

#include "./regexp.h"

namespace libj {
namespace glue {

RegExp* RegExp::create(const std::u16string& pattern, unsigned int flags) {
    RegExp* re = new RegExp(pattern, flags);
    iv::core::Space space;
    int fs = (flags & IGNORE_CASE ? iv::aero::IGNORE_CASE : 0)
           | (flags & MULTILINE ? iv::aero::MULTILINE : 0);
    int error = 0;
    re->code_ = iv::aero::Compile(&space, pattern, fs, &error);
    if (!error && re->code_) {
        return re;
    } else {
        delete re;
        return NULL;
    }
}

RegExp::~RegExp() {
    delete static_cast<iv::aero::Code*>(code_);
}

bool RegExp::global() const {
    return flags_ & GLOBAL;
}

bool RegExp::ignoreCase() const {
    return flags_ & IGNORE_CASE;
}

bool RegExp::multiline() const {
    return flags_ & MULTILINE;
}

int RegExp::execute(
    const std::u16string& str,
    int offset,
    std::vector<int>& captures) const {
    static iv::aero::VM vm;
    iv::aero::Code* code = static_cast<iv::aero::Code*>(code_);
    captures.clear();
    Size n = code->captures() * 2;
    for (Size i = 0; i < n; i++)
        captures.push_back(-1);
    return vm.Execute(code, str, captures.data(), offset);
}

}  // namespace glue
}  // namespace libj
