// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/js_closure.h>
#include <libj/detail/js_closure.h>

namespace libj {

JsClosure::Ptr JsClosure::create(JsLambda lambda) {
    return Ptr(new detail::JsClosure<JsClosure>(lambda));
}

}  // namespace libj
