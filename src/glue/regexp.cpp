// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/config.h>
#include <libj/glue/regexp.h>

#include <pcre.h>
#include <string>

namespace libj {
namespace glue {

class RegExpBase : public RegExp {
 public:
    RegExpBase(unsigned flags) : flags_(flags) {}

    virtual bool global() const {
        return !!(flags_ & GLOBAL);
    }

    virtual bool ignoreCase() const {
        return !!(flags_ & IGNORE_CASE);
    }

    virtual bool multiline() const {
        return !!(flags_ & MULTILINE);
    }

 protected:
    unsigned flags_;
};

class RegExpImpl : public RegExpBase {
 public:
    RegExpImpl(const void* pattern, int len, unsigned flags)
        : RegExpBase(flags) {
        const char* errorMessage = NULL;
        re_ = jsRegExpCompile(
            static_cast<const uint16_t*>(pattern),
            len,
            ignoreCase()
                ? dart::jscre::JSRegExpIgnoreCase
                : dart::jscre::JSRegExpDoNotIgnoreCase,
            multiline()
                ? dart::jscre::JSRegExpMultiline
                : dart::jscre::JSRegExpSingleLine,
            &numSubpatterns_,
            &errorMessage,
            malloc,
            free);
    }

    virtual ~RegExpImpl() {
        jsRegExpFree(re_, free);
    }

    virtual bool execute(
        const void* str,
        int len,
        int offset,
        std::vector<int>& captures) const {
        int num = numSubpatterns_ + 1;
        int csLen = num * 3;
        int* cs = new int[csLen];
        int r = dart::jscre::jsRegExpExecute(
            re_, static_cast<const uint16_t*>(str), len, offset, cs, csLen);
        captures.clear();
        for (int i = 0; i < num; i++) {
            captures.push_back(cs[i * 2]);
            captures.push_back(cs[i * 2 + 1]);
        }
        delete[] cs;
        return r >= 0;
    }

    bool valid() const {
        return !!re_;
    }

 private:
    unsigned numSubpatterns_;
    dart::jscre::JSRegExp* re_;
};

RegExp::Encoding RegExp::encoding() {
    return UTF16;
}

RegExp* RegExp::create(const void* pattern, int len, unsigned flags) {
    RegExpImpl* re = new RegExpImpl(pattern, len, flags);
    if (re->valid()) {
        return re;
    } else {
        delete re;
        return NULL;
    }
}

}  // namespace glue
}  // namespace libj
