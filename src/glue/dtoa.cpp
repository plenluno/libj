// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/glue/dtoa.h>

// type mismatch between definition and declaration
// #include <iv/lv5/third_party/v8_dtoa/conversions.h>

namespace v8 {
namespace internal {

char* DoubleToCString(double value, char* buffer, int buflen);

}  // namespace internal
}  // namespace v8

namespace libj {
namespace glue {
namespace dtoa {

void doubleToString(double d, char* buf, size_t len) {
    v8::internal::DoubleToCString(d, buf, len);
}

}  // namespace dtoa
}  // namespace glue
}  // namespace libj
