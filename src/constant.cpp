// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/constant.h>

#include <limits>

namespace libj {

const Size NO_POS = static_cast<Size>(-1);

const Size NO_SIZE = static_cast<Size>(-1);

const Char NO_CHAR = static_cast<Char>(-1);

const Value UNDEFINED;

const Double QUIET_NAN = std::numeric_limits<Double>::quiet_NaN();

const Double SIGNALING_NAN = std::numeric_limits<Double>::signaling_NaN();

const Double POSITIVE_INFINITY = std::numeric_limits<Double>::infinity();

const Double NEGATIVE_INFINITY = -std::numeric_limits<Double>::infinity();

}  // namespace libj
