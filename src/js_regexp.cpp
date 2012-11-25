// Copyright (c) 2012 Plenluno All rights reserved.

#include <assert.h>
#include <vector>

#include "libj/js_regexp.h"
#include "libj/symbol.h"
#include "libj/glue/regexp.h"
#include "libj/bridge/abstract_js_object.h"

namespace libj {

typedef bridge::AbstractJsObject<JsRegExp> JsRegExpBase;

class JsRegExpImpl : public JsRegExpBase {
 public:
    static Ptr create(String::CPtr pattern, UInt flags) {
        JsRegExpImpl* impl = new JsRegExpImpl(pattern, flags);
        if (impl->re_) {
            return Ptr(impl);
        } else {
            delete impl;
            return null();
        }
    }

    Boolean global() const {
        return re_->global();
    }

    Boolean ignoreCase() const {
        return re_->ignoreCase();
    }

    Boolean multiline() const {
        return re_->multiline();
    }

    String::CPtr source() const {
        return pattern_;
    }

    JsArray::Ptr exec(String::CPtr str) const {
        LIBJ_STATIC_SYMBOL_DEF(symIndex, "index");
        LIBJ_STATIC_SYMBOL_DEF(symInput, "input");

        if (!str) {
            return JsArray::null();
        }

        std::vector<int> captures;
        if (!re_->execute(str, 0, captures)) {
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

    Boolean test(String::CPtr str) const {
        return !!exec(str);
    }

 private:
    String::CPtr pattern_;
    glue::RegExp* re_;

    JsRegExpImpl(String::CPtr pattern, UInt flags)
        : JsRegExpBase(JsObject::create())
        , pattern_(pattern)
        , re_(glue::RegExp::create(pattern, flags)) {}

 public:
    ~JsRegExpImpl() {
        delete re_;
    }
};

JsRegExp::Ptr JsRegExp::create(String::CPtr pattern, UInt flags) {
    return JsRegExpImpl::create(pattern, flags);
}

}  // namespace libj
