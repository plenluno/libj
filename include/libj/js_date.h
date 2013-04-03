// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_JS_DATE_H_
#define LIBJ_JS_DATE_H_

#include <libj/js_object.h>

namespace libj {

class JsDate : LIBJ_JS_OBJECT(JsDate)
 public:
    static Ptr create();

    static Ptr create(Double value);

    static Ptr create(String::CPtr dateStr);

    static Ptr create(
        Int year,
        Int month,
        Int day,
        Int hour = 0,
        Int minute = 0,
        Int second = 0,
        Int millisecond = 0);

    static Double now();

    static Double parse(String::CPtr dateStr);

    virtual Int getDate() const = 0;

    virtual Int getDay() const = 0;

    virtual Int getFullYear() const = 0;

    virtual Int getHours() const = 0;

    virtual Int getMilliseconds() const = 0;

    virtual Int getMinutes() const = 0;

    virtual Int getMonth() const = 0;

    virtual Int getSeconds() const = 0;

    virtual Double getTime() const = 0;

    virtual Int getTimezoneOffset() = 0;

    virtual Int getUTCDate() const = 0;

    virtual Int getUTCDay() const = 0;

    virtual Int getUTCFullYear() const = 0;

    virtual Int getUTCHours() const = 0;

    virtual Int getUTCMilliseconds() const = 0;

    virtual Int getUTCMinutes() const = 0;

    virtual Int getUTCMonth() const = 0;

    virtual Int getUTCSeconds() const = 0;

    virtual Double setDate(Int date) = 0;

    virtual Double setFullYear(Int year) = 0;

    virtual Double setHours(Int hour) = 0;

    virtual Double setMilliseconds(Int ms) = 0;

    virtual Double setMinutes(Int min) = 0;

    virtual Double setMonth(Int month) = 0;

    virtual Double setSeconds(Int sec) = 0;

    virtual Double setTime(Double value) = 0;

    virtual Double setUTCDate(Int date) = 0;

    virtual Double setUTCFullYear(Int year) = 0;

    virtual Double setUTCHours(Int hour) = 0;

    virtual Double setUTCMilliseconds(Int ms) = 0;

    virtual Double setUTCMinutes(Int min) = 0;

    virtual Double setUTCMonth(Int month) = 0;

    virtual Double setUTCSeconds(Int sec) = 0;

    virtual String::CPtr toDateString() const = 0;

    virtual String::CPtr toISOString() const = 0;

    virtual String::CPtr toJSON() const = 0;

    virtual String::CPtr toTimeString() const = 0;

    virtual String::CPtr toUTCString() const = 0;
};

}  // namespace libj

#endif  // LIBJ_JS_DATE_H_
