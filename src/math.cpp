// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/math.h>
#include <libj/constant.h>

#include <iv/xorshift.h>
#include <iv/random_generator.h>

#include <cmath>

namespace libj {
namespace math {

Double abs(Double x) {
    return std::abs(x);
}

Double acos(Double x) {
    return std::acos(x);
}

Double asin(Double x) {
    return std::asin(x);
}

Double atan(Double x) {
    return std::atan(x);
}

Double atan2(Double y, Double x) {
    return std::atan2(y, x);
}

Double ceil(Double x) {
    return std::ceil(x);
}

Double cos(Double x) {
    return std::cos(x);
}

Double exp(Double x) {
    return std::exp(x);
}

Double floor(Double x) {
    return std::floor(x);
}

Double log(Double x) {
    return std::log(x);
}

Double max(Double x, Double y) {
    if (std::isnan(x)) {
        return x;
    } else if (std::isnan(y)) {
        return y;
    } else if (x > y) {
        return x;
    } else if (x == 0.0 && y == 0.0 && !std::signbit(x)) {
        return x;
    } else {
        return y;
    }
}

Double min(Double x, Double y) {
    if (std::isnan(x)) {
        return x;
    } else if (std::isnan(y)) {
        return y;
    } else if (x < y) {
        return x;
    } else if (x == 0.0 && y == 0.0 && std::signbit(x)) {
        return x;
    } else {
        return y;
    }
}

Double pow(Double x, Double y) {
    if (y == 0.0) {
        return 1.0;
    } else if (std::isnan(y)) {
        return QUIET_NAN;
    } else if ((x == 1.0 || x == -1.0) && std::isinf(y)) {
        return QUIET_NAN;
    } else {
        return std::pow(x, y);
    }
}

Double random() {
    static iv::core::UniformRandomGenerator<iv::core::Xor128> random;
    return random.get();
}

Double sin(Double x) {
    return std::sin(x);
}

Double sqrt(Double x) {
    return std::sqrt(x);
}

Double tan(Double x) {
    return std::tan(x);
}

}  // namespace math
}  // namespace libj
