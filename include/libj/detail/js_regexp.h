// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_REGEXP_H_
#define LIBJ_DETAIL_JS_REGEXP_H_

#include <assert.h>
#include <string>
#include <vector>

#include "libj/endian.h"
#include "libj/glue/regexp.h"

#include "./js_object.h"

namespace libj {
namespace detail {

template<typename I>
class JsRegExp : public JsObject<I> {
 public:
    JsRegExp(String::CPtr pattern, UInt flags)
        : pattern_(pattern)
        , re_(NULL) {
        if (pattern) {
            re_ = glue::RegExp::create(toStdString(pattern), flags);
        }
    }

    virtual ~JsRegExp() {
        delete re_;
    }

    Boolean valid() const {
        return !!re_;
    }

    virtual Boolean global() const {
        return re_->global();
    }

    virtual Boolean ignoreCase() const {
        return re_->ignoreCase();
    }

    virtual Boolean multiline() const {
        return re_->multiline();
    }

    virtual String::CPtr source() const {
        return pattern_;
    }

    virtual JsArray::Ptr exec(String::CPtr str) const {
        LIBJ_STATIC_SYMBOL_DEF(symIndex, "index");
        LIBJ_STATIC_SYMBOL_DEF(symInput, "input");

        if (!str) {
            return JsArray::null();
        }

        std::vector<int> captures;
        if (!re_->execute(toStdString(str), 0, captures)) {
            return JsArray::null();
        }

        JsArray::Ptr res = JsArray::create();
        Size len = captures.size();
        assert(len > 0);
        for (Size i = 0; i < len; i += 2) {
            if (captures[i] >= 0 &&
                captures[i+1] >= 0 &&
                captures[i] < captures[i+1] &&
                captures[i+1] <= static_cast<int>(str->length())) {
                res->add(str->substring(captures[i], captures[i+1]));
            } else {
                res->add(UNDEFINED);
            }
        }
        res->setProperty(symInput, str);
        res->setProperty(symIndex, captures[0]);
        return res;
    }

    virtual Boolean test(String::CPtr str) const {
        return !!exec(str);
    }

 private:
    static std::string toStdString(String::CPtr s) {
        static Boolean big = endian() == BIG;
        assert(s);
        glue::RegExp::Encoding enc = glue::RegExp::encoding();
        switch (enc) {
        case glue::RegExp::UTF8:
            return s->toStdString();
        case glue::RegExp::UTF16:
            if (big) {
                return s->toStdString(String::UTF16BE);
            } else {
                return s->toStdString(String::UTF16LE);
            }
        case glue::RegExp::UTF32:
            if (big) {
                return s->toStdString(String::UTF16BE);
            } else {
                return s->toStdString(String::UTF16LE);
            }
        default:
            assert(false);
            return s->toStdString();
        }
    }

 private:
    String::CPtr pattern_;
    glue::RegExp* re_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_REGEXP_H_
