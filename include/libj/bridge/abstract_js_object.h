// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_
#define LIBJ_BRIDGE_ABSTRACT_JS_OBJECT_H_

#include <libj/js_object.h>
#include <libj/bridge/abstract_map.h>

namespace libj {
namespace bridge {

template<typename I>
class AbstractJsObject : public AbstractMap<I> {
 public:
    AbstractJsObject(JsObject::Ptr obj = JsObject::create())
        : AbstractMap<I>(obj)
        , obj_(obj) {}

    virtual Boolean containsKey(const Value& key) const {
        return obj_->containsKey(key);
    }

    virtual Boolean containsKey(String::CPtr key) const {
        return obj_->containsKey(key);
    }

    virtual Value get(const Value& key) const {
        return obj_->get(key);
    }

    virtual Value get(String::CPtr key) const {
        return obj_->get(key);
    }

    virtual Value put(const Value& key, const Value& val) {
        return obj_->put(key, val);
    }

    virtual Value put(String::CPtr key, const Value& val) {
        return obj_->put(key, val);
    }

    virtual Value remove(const Value& key) {
        return obj_->remove(key);
    }

    virtual Value remove(String::CPtr key) {
        return obj_->remove(key);
    }

    virtual Boolean hasProperty(const Value& name) const {
        return obj_->hasProperty(name);
    }

    virtual Boolean hasProperty(String::CPtr name) const {
        return obj_->hasProperty(name);
    }

    virtual Value getProperty(const Value& name) const {
        return obj_->getProperty(name);
    }

    virtual Value getProperty(String::CPtr name) const {
        return obj_->getProperty(name);
    }

    virtual Value setProperty(const Value& name, const Value& val) {
        return obj_->setProperty(name, val);
    }

    virtual Value setProperty(String::CPtr name, const Value& val) {
        return obj_->setProperty(name, val);
    }

    virtual Value deleteProperty(const Value& name) {
        return obj_->deleteProperty(name);
    }

    virtual Value deleteProperty(String::CPtr name) {
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
