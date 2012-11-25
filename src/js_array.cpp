// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/js_array.h"
#include "libj/detail/js_array.h"

namespace libj {

JsArray::Ptr JsArray::create() {
    return Ptr(new detail::JsArray<JsArray>());
}

JsArray::Ptr JsArray::create(ArrayList::CPtr list) {
    if (!list) return null();

    JsArray::Ptr ary(JsArray::create());
    ary->addAll(list);
    return ary;
}

}  // namespace libj
