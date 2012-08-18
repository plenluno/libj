// Copyright (c) 2012 Plenluno All rights reserved.

#include <vector>

#include "libj/js_regexp.h"
#include "libj/undefined.h"
#include "./glue/regexp.h"

namespace libj {

static glue::RegExp::U16String toU16String(String::CPtr str) {
    if (Type<std::char16_t>::id() == Type<uint16_t>::id()) {
        return str->toStdU16String();
    } else {
        glue::RegExp::U16String s;
        std::u16string ss = str->toStdU16String();
        for (size_t i = 0; i < ss.length(); i++) {
            s.push_back(ss[i]);
        }
        return s;
    }
}

class JsRegExpImpl : public JsRegExp {
 public:
    static Ptr create(String::CPtr pattern, UInt flags) {
        JsRegExpImpl* impl = new JsRegExpImpl(pattern, flags);
        if (impl->re_) {
            Ptr p(impl);
            return p;
        } else {
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
        if (!str) {
            return JsArray::null();
        }

        std::vector<int> captures;
        re_->execute(toU16String(str), 0, captures);
        if (captures.empty()) {
            return JsArray::null();
        }

        JsArray::Ptr res = JsArray::create();
        Size len = captures.size();
        for (Size i = 0; i < len; i += 2) {
            if (captures[i] >= 0 &&
                captures[i+1] >= 0 &&
                captures[i] < captures[i+1] &&
                captures[i+1] <= static_cast<int>(str->length())) {
                res->add(str->substring(captures[i], captures[i+1]));
            } else {
                res->add(Undefined::instance());
            }
        }
        return res;
    }

    Boolean test(String::CPtr str) const {
        return !!exec(str);
    }

 private:
    JsObject::Ptr obj_;
    String::CPtr pattern_;
    glue::RegExp* re_;

    JsRegExpImpl(String::CPtr pattern, UInt flags)
        : obj_(JsObject::create())
        , pattern_(pattern)
        , re_(glue::RegExp::create(toU16String(pattern), flags)) {}

 public:
    ~JsRegExpImpl() {
        delete re_;
    }

    LIBJ_JS_OBJECT_IMPL(obj_);
};

JsRegExp::Ptr JsRegExp::create(String::CPtr pattern, UInt flags) {
    return JsRegExpImpl::create(pattern, flags);
}

}  // namespace libj
