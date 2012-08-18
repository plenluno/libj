// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/js_array.h"
#include "libj/js_object.h"

namespace libj {

class JsArrayImpl : public JsArray {
 public:
    static Ptr create() {
        Ptr p(new JsArrayImpl());
        return p;
    }

    Boolean hasProperty(const Value& name) const {
        return obj_->hasProperty(name);
    }

    Value getProperty(const Value& name) const {
        return obj_->getProperty(name);
    }

    void setProperty(const Value& name, const Value& val) {
        obj_->setProperty(name, val);
    }

    void deleteProperty(const Value& name) {
        obj_->deleteProperty(name);
    }

 private:
    JsObject::Ptr obj_;
    ArrayList::Ptr ary_;

    JsArrayImpl()
        : obj_(JsObject::create())
        , ary_(ArrayList::create()) {}

    LIBJ_LIST_IMPL(ary_);
};

JsArray::Ptr JsArray::create() {
    return JsArrayImpl::create();
}

JsArray::Ptr JsArray::create(ArrayList::CPtr list) {
    JsArray::Ptr ary = JsArray::create();
    ary->addAll(list);
    return ary;
}

}  // namespace libj
