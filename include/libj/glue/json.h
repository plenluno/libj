// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_GLUE_JSON_H_
#define LIBJ_GLUE_JSON_H_

#include "libj/string.h"
#include "libj/value.h"

namespace libj {
namespace glue {
namespace json {

Value parse(String::CPtr str);

}  // namespace json
}  // namespace glue
}  // namespace libj

#endif  // LIBJ_GLUE_JSON_H_
