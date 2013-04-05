// Copyright (c) 2012-2013 Plenluno All rights reserved.

#ifndef LIBJ_GLUE_DTOA_H_
#define LIBJ_GLUE_DTOA_H_

#include <stddef.h>

namespace libj {
namespace glue {
namespace dtoa {

void doubleToString(double d, char* buf, size_t len);

}  // namespace dtoa
}  // namespace glue
}  // namespace libj

#endif  // LIBJ_GLUE_DTOA_H_
