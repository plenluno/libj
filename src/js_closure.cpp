// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/js_closure.h>
#include <libj/detail/js_closure.h>

#ifdef LIBJ_USE_CXX11

namespace libj {

JsClosure::Ptr JsClosure::create(JsLambda lambda) {
    return Ptr(new detail::JsClosure<JsClosure>(lambda));
}

}  // namespace libj

#endif  // LIBJ_USE_CXX11
