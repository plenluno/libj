// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_JSON_H_
#define LIBJ_JSON_H_

#include "libj/string.h"

namespace libj {
namespace json {

Value parse(Type<String>::Cptr str);
Type<String>::Cptr stringify(const Value& val);


}  // namespace json
}  // namespace libj

#endif  // LIBJ_JSON_H_