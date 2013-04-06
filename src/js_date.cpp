// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/math.h>
#include <libj/detail/js_date.h>

namespace libj {

JsDate::Ptr JsDate::create() {
    return Ptr(new detail::JsDate());
}

JsDate::Ptr JsDate::create(Double value) {
    return Ptr(new detail::JsDate(value));
}

JsDate::Ptr JsDate::create(String::CPtr dateStr) {
    return Ptr(new detail::JsDate(dateStr));
}

JsDate::Ptr JsDate::create(
    Int year,
    Int month,
    Int day,
    Int hour,
    Int minute,
    Int second,
    Int millisecond) {
    return Ptr(new detail::JsDate(
        year,
        month,
        day,
        hour,
        minute,
        second,
        millisecond));
}

Double JsDate::now() {
    return math::floor(iv::core::date::CurrentTime());
}

Double JsDate::parse(String::CPtr dateStr) {
#ifdef LIBJ_USE_UTF16
    return iv::core::date::Parse(dateStr->toStdU16String());
#else
    return iv::core::date::Parse(dateStr->toStdU32String());
#endif
}

}  // namespace libj
