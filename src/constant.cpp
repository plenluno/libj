// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libj/constant.h>

#include <limits>

namespace libj {

const Size NO_POS = -1;

const Size NO_SIZE = -1;

const Char NO_CHAR = -1;

const Double INFINITY = std::numeric_limits<Double>::infinity();

const Double QUIET_NAN = std::numeric_limits<Double>::quiet_NaN();

const Value UNDEFINED;

}  // namespace libj
