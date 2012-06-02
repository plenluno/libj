// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/js_object.h"

namespace libj {

class JsObjectImpl : public JsObject {
 private:
    static String::CPtr STR_OBJECT;

 public:
    static Ptr create() {
        Ptr p(new JsObjectImpl());
        return p;
    }

    Value put(const Value& key, const Value& val) {
        return map_->put(String::valueOf(key), val);
    }

    String::CPtr toString() const {
        return STR_OBJECT;
    }

    Size size() const {
        return map_->size();
    }

    Value get(const Value& key) const {
        return map_->get(key);
    }

    Value remove(const Value& key) {
        return map_->remove(key);
    }

    Set::CPtr keySet() const {
        return map_->keySet();
    }

    void clear() {
        map_->clear();
    }

 private:
    Map::Ptr map_;

    JsObjectImpl() : map_(Map::create()) {}
};

String::CPtr JsObjectImpl::STR_OBJECT = String::create("[object Object]");

JsObject::Ptr JsObject::create() {
    return JsObjectImpl::create();
}

}  // namespace libj
