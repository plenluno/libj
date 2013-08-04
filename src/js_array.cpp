// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/js_array.h>
#include <libj/detail/js_array.h>

namespace libj {

JsArray::Ptr JsArray::create(Size length) {
    detail::JsArray<JsArray>* a = new detail::JsArray<JsArray>();
    for (Size i = 0; i < length; i++) {
        a->add(UNDEFINED);
    }
    return Ptr(a);
}

JsArray::Ptr JsArray::create(ArrayList::CPtr list) {
    if (!list) return null();

    JsArray::Ptr ary = JsArray::create();
    ary->addAll(list);
    return ary;
}

}  // namespace libj
