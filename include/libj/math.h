// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_MATH_H_
#define LIBJ_MATH_H_

#include <libj/typedef.h>

namespace libj {
namespace math {

extern const Double E;

extern const Double LN10;

extern const Double LN2;

extern const Double LOG10E;

extern const Double LOG2E;

extern const Double PI;

extern const Double SQRT1_2;

extern const Double SQRT2;

Double abs(Double x);

Double acos(Double x);

Double asin(Double x);

Double atan(Double x);

Double atan2(Double y, Double x);

Double ceil(Double x);

Double cos(Double x);

Double exp(Double x);

Double floor(Double x);

Double log(Double x);

Double max(Double x, Double y);

Double min(Double x, Double y);

Double pow(Double x, Double y);

Double random();

Double sin(Double x);

Double sqrt(Double x);

Double tan(Double x);

}  // namespace math
}  // namespace libj

#endif  // LIBJ_MATH_H_
