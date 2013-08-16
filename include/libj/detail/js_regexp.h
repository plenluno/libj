// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_REGEXP_H_
#define LIBJ_DETAIL_JS_REGEXP_H_

#include <libj/glue/regexp.h>
#include <libj/detail/js_object.h>

#include <assert.h>
#include <string>
#include <vector>

namespace libj {
namespace detail {

template<typename I>
class JsRegExp : public JsObject<I> {
 public:
    JsRegExp(String::CPtr pattern, UInt flags)
        : pattern_(pattern)
        , re_(NULL) {
        if (pattern) {
            if (glue::RegExp::encoding() == encoding()) {
                re_ = glue::RegExp::create(
                    pattern->data(), pattern->length(), flags);
            } else {
                std::string pat = toStdString(pattern);
                re_ = glue::RegExp::create(
                    pat.data(), getLength(pat), flags);
            }
        }
        setLastIndex(0);
    }

    virtual ~JsRegExp() {
        delete re_;
    }

    Boolean valid() const {
        return !!re_;
    }

    virtual Boolean global() const {
        return re_ && re_->global();
    }

    virtual Boolean ignoreCase() const {
        return re_ && re_->ignoreCase();
    }

    virtual Boolean multiline() const {
        return re_ && re_->multiline();
    }

    virtual String::CPtr source() const {
        return pattern_;
    }

    virtual Size lastIndex() const {
        LIBJ_STATIC_SYMBOL_DEF(symLastIndex, "lastIndex");
        return to<Size>(this->get(symLastIndex));
    }

    virtual JsArray::Ptr exec(String::CPtr str) {
        LIBJ_STATIC_SYMBOL_DEF(symIndex, "index");
        LIBJ_STATIC_SYMBOL_DEF(symInput, "input");

        if (!str) return execFail();

        Size lastIndex = 0;
        Boolean global = this->global();
        if (global) {
            lastIndex = this->lastIndex();
            if (lastIndex > str->length()) {
                return execFail();
            } else {
                str = str->substring(lastIndex);
            }
        }

        int len;
        std::vector<int> captures;
        Boolean success;
        if (glue::RegExp::encoding() == encoding()) {
            len = str->length();
            success = re_->execute(str->data(), len, 0, captures);
        } else {
            std::string s = toStdString(str);
            len = getLength(s);
            success = re_->execute(s.data(), len, 0, captures);
        }

        if (!success) return execFail();

        if (global) setLastIndex(lastIndex + (captures[1] - captures[0]));

        JsArray::Ptr res = JsArray::create();
        Size size = captures.size();
        assert(size > 0);
        for (Size i = 0; i < size; i += 2) {
            if (captures[i] >= 0 &&
                captures[i+1] >= 0 &&
                captures[i] <= captures[i+1] &&
                captures[i+1] <= len) {
                res->add(str->substring(captures[i], captures[i+1]));
            } else {
                res->add(UNDEFINED);
            }
        }
        res->setProperty(symInput, str);
        res->setProperty(symIndex, captures[0]);
        return res;
    }

    virtual Boolean test(String::CPtr str) {
        return !!exec(str);
    }

 private:
    static glue::RegExp::Encoding encoding() {
#ifdef LIBJ_USE_UTF32
        return glue::RegExp::UTF32;
#else
        return glue::RegExp::UTF16;
#endif
    }

    static std::string toStdString(String::CPtr s) {
        assert(s);
        switch (glue::RegExp::encoding()) {
        case glue::RegExp::UTF8:
            return s->toStdString(String::UTF8);
        case glue::RegExp::UTF16:
            return s->toStdString(String::UTF16);
        case glue::RegExp::UTF32:
            return s->toStdString(String::UTF32);
        default:
            assert(false);
            return std::string();
        }
    }

    static int getLength(const std::string& str) {
        int len = str.length();
        switch (glue::RegExp::encoding()) {
        case glue::RegExp::UTF8:
            return len;
        case glue::RegExp::UTF16:
            assert(len % 2 == 0 && len >= 2);
            return (len / 2) - 1;
        case glue::RegExp::UTF32:
            assert(len % 4 == 0 && len >= 4);
            return (len / 4) - 1;
        default:
            assert(false);
            return 0;
        }
    }

    void setLastIndex(Size lastIndex) {
        LIBJ_STATIC_SYMBOL_DEF(symLastIndex, "lastIndex");
        this->put(symLastIndex, lastIndex);
    }

    JsArray::Ptr execFail() {
        if (global()) setLastIndex(0);
        return JsArray::null();
    }

 private:
    String::CPtr pattern_;
    glue::RegExp* re_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_REGEXP_H_
