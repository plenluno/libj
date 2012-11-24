// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_
#define LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_

#include "libj/js_object.h"
#include "libj/string.h"

#include "./abstract_map.h"

namespace libj {
namespace bridge {

template<typename T>
class AbstractJsObject : public AbstractMap<T> {
 public:
    AbstractJsObject(JsObject::Ptr obj)
        : AbstractMap<T>(obj)
        , obj_(obj) {}

    virtual String::CPtr toString() const {
        return obj_->toString();
    }

 private:
    JsObject::Ptr obj_;
};

}  // namespace bridge
}  // namespace libj

#endif  // LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_
