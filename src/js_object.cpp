// Copyright (c) 2012 Plenluno All rights reserved.

#include "libj/js_object.h"
#include "libj/detail/js_object.h"

namespace libj {

JsObject::Ptr JsObject::create() {
    return Ptr(new detail::JsObject<JsObject>());
}

}  // namespace libj
