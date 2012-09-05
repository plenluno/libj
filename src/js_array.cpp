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

 private:
    JsObject::Ptr obj_;
    ArrayList::Ptr ary_;

    JsArrayImpl()
        : obj_(JsObject::create())
        , ary_(ArrayList::create()) {}

    LIBJ_LIST_IMPL(ary_);
    LIBJ_JS_PROPERTY_IMPL(obj_);
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
