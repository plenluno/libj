// Copyright (c) 2012 Plenluno All rights reserved.

#include <iv/aero/aero.h>

#include "./regexp.h"

namespace libj {
namespace glue {

RegExp* RegExp::create(const std::u16string& pattern, unsigned int flags) {
    int f = (flags & IGNORE_CASE ? iv::aero::IGNORE_CASE : 0)
          | (flags & MULTILINE ? iv::aero::MULTILINE : 0);
    RegExp* re = new RegExp(pattern, f);
    iv::core::Space space;
    int error = 0;
    re->code_ = iv::aero::Compile(&space, pattern, f, &error);
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

bool RegExp::ignoreCase() const {
    return flags_ & iv::aero::IGNORE_CASE;
}

bool RegExp::multiline() const {
    return flags_ & iv::aero::MULTILINE;
}

int RegExp::execute(
    const std::u16string& str,
    int offset,
    std::vector<int>& captures) const {
    static iv::aero::VM vm;
    iv::aero::Code* code = static_cast<iv::aero::Code*>(code_);
    captures.clear();
    Size n = (code->captures() + 1) * 2;
    for (Size i = 0; i < n; i++)
        captures.push_back(-1);
    return vm.Execute(code, str, captures.data(), offset);
}

}  // namespace glue
}  // namespace libj
