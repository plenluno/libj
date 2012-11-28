// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_
#define LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_

#include <libj/js_object.h>
#include <libj/string.h>
#include <libj/bridge/abstract_map.h>

namespace libj {
namespace bridge {

template<typename I>
class AbstractJsObject : public AbstractMap<I> {
 public:
    AbstractJsObject(JsObject::Ptr obj = JsObject::create())
        : AbstractMap<I>(obj)
        , obj_(obj) {}

    virtual Boolean hasProperty(const Value& name) const {
        return obj_->hasProperty(name);
    }

    virtual Value getProperty(const Value& name) const {
        return obj_->getProperty(name);
    }

    virtual Value setProperty(const Value& name, const Value& val) {
        return obj_->setProperty(name, val);
    }

    virtual Value deleteProperty(const Value& name) {
        return obj_->deleteProperty(name);
    }

    virtual String::CPtr toString() const {
        return obj_->toString();
    }

 private:
    JsObject::Ptr obj_;
};

}  // namespace bridge
}  // namespace libj

#endif  // LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_
