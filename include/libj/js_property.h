// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JS_PROPERTY_H_
#define LIBJ_JS_PROPERTY_H_

#include "libj/js_object.h"

namespace libj {

class JsPropertyMixin {
 public:
    Boolean hasProperty(const Value& name) const {
        return obj_->hasProperty(name);
    }

    Value getProperty(const Value& name) const {
        return obj_->getProperty(name);
    }

    Value setProperty(const Value& name, const Value& val) {
        return obj_->setProperty(name, val);
    }

    Value deleteProperty(const Value& name) {
        return obj_->deleteProperty(name);
    }

 protected:
    JsObject::Ptr obj_;

    JsPropertyMixin() : obj_(JsObject::create()) {}
};

}  // namespace libj

#endif  // LIBJ_JS_PROPERTY_H_
