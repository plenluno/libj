// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/config.h>
#include <libj/glue/regexp.h>

#ifdef LIBJ_USE_JSCRE
    #include <pcre.h>
#else
    #include <iv/aero/aero.h>
    #include <vector>
#endif

#include <string>

namespace libj {
namespace glue {

typedef std::basic_string<uint16_t> U16String;

static U16String toU16String(const std::string& str) {
    return U16String(reinterpret_cast<const uint16_t*>(str.c_str()));
}

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

#ifdef LIBJ_USE_JSCRE

class RegExpImpl : public RegExpBase {
 public:
    RegExpImpl(const U16String& pattern, unsigned flags)
        : RegExpBase(flags)
        , pattern_(pattern) {
        const char* errorMessage = NULL;
        re_ = jsRegExpCompile(
            pattern.c_str(),
            pattern.length(),
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
        const std::string& str,
        int offset,
        std::vector<int>& captures) const {
        U16String subject = toU16String(str);
        int num = numSubpatterns_ + 1;
        int len = num * 3;
        int* cs = new int[len];
        int r = dart::jscre::jsRegExpExecute(
            re_, subject.c_str(), subject.length(), offset, cs, len);
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
    U16String pattern_;
    unsigned numSubpatterns_;
    dart::jscre::JSRegExp* re_;
};

#else

class RegExpImpl : public RegExpBase {
 public:
    RegExpImpl(const U16String& pattern, unsigned flags)
        : RegExpBase(flags)
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

 private:
    iv::aero::Code* code_;
};

#endif

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
