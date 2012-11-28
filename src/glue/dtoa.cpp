// Copyright (c) 2012 Plenluno All rights reserved.

#include <libj/glue/dtoa.h>

#include <iv/lv5/third_party/v8_dtoa/conversions.h>

namespace libj {
namespace glue {
namespace dtoa {

String::CPtr doubleToString(Double d) {
    const Size kLen = 64;
    char s[kLen];
    return String::create(v8::internal::DoubleToCString(d, s, kLen));
}

}  // namespace dtoa
}  // namespace glue
}  // namespace libj
