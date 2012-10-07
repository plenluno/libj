// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/js_object.h"

namespace libj {

class JsObjectImpl : public JsObject {
 public:
    static Ptr create() {
        return Ptr(new JsObjectImpl());
    }

    void clear() {
        map_->clear();
    }

    Boolean containsKey(const Value& key) const {
        return map_->containsKey(String::valueOf(key));
    }

    Boolean containsValue(const Value& val) const {
        return map_->containsValue(val);
    }

    Value get(const Value& key) const {
        return map_->get(String::valueOf(key));
    }

    Set::CPtr keySet() const {
        return map_->keySet();
    }

    Value put(const Value& key, const Value& val) {
        return map_->put(String::valueOf(key), val);
    }

    Value remove(const Value& key) {
        return map_->remove(String::valueOf(key));
    }

    Size size() const {
        return map_->size();
    }

    String::CPtr toString() const {
        const String::CPtr strObject = String::create("[object Object]");
        return strObject;
    }

 private:
    Map::Ptr map_;

    JsObjectImpl() : map_(Map::create()) {}
};

JsObject::Ptr JsObject::create() {
    return JsObjectImpl::create();
}

}  // namespace libj
