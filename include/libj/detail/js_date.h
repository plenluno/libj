// Copyright (c) 2013 Plenluno All rights reserved.

#ifndef LIBJ_DETAIL_JS_DATE_H_
#define LIBJ_DETAIL_JS_DATE_H_

#include <libj/js_date.h>
#include <libj/detail/js_object.h>

#if defined(LIBJ_PF_UNIX) && !defined(LIBJ_USE_CXX11) \
 || defined(LIBJ_PF_ANDROID)
    #define IV_OS_BSD
#endif

#include <iv/date_utils.h>
#include <iv/date_parser.h>

namespace libj {
namespace detail {

class JsDate : public JsObject<libj::JsDate> {
 public:
    JsDate() {
        set(iv::core::date::CurrentTime());
    }

    JsDate(Double value) {
        set(value);
    }

    JsDate(String::CPtr dateStr) {
        set(JsDate::parse(dateStr));
    }

    JsDate(
        Int year,
        Int month,
        Int day,
        Int hour,
        Int minute,
        Int second,
        Int millisecond) {
        Double value =
            iv::core::date::UTC(
                iv::core::date::MakeDate(
                    iv::core::date::MakeDay(
                        year,
                        month,
                        day),
                    iv::core::date::MakeTime(
                        hour,
                        minute,
                        second,
                        millisecond)));
        set(value);
    }

    virtual Int getDate() const {
        return local_.date();
    }

    virtual Int getDay() const {
        return local_.weekday();
    }

    virtual Int getFullYear() const {
        return local_.year();
    }

    virtual Int getHours() const {
        return local_.hour();
    }

    virtual Int getMilliseconds() const {
        return local_.ms();
    }

    virtual Int getMinutes() const {
        return local_.min();
    }

    virtual Int getMonth() const {
        return local_.month();
    }

    virtual Int getSeconds() const {
        return local_.sec();
    }

    virtual Double getTime() const {
        return utc_.value();
    }

    virtual Int getTimezoneOffset() {
        return timezone_;
    }

    virtual Int getUTCDate() const {
        return utc_.date();
    }

    virtual Int getUTCDay() const {
        return utc_.weekday();
    }

    virtual Int getUTCFullYear() const {
        return utc_.year();
    }

    virtual Int getUTCHours() const {
        return utc_.hour();
    }

    virtual Int getUTCMilliseconds() const {
        return utc_.ms();
    }

    virtual Int getUTCMinutes() const {
        return utc_.min();
    }

    virtual Int getUTCMonth() const {
        return utc_.month();
    }

    virtual Int getUTCSeconds() const {
        return utc_.sec();
    }

    virtual Double setDate(Int date) {
        return setDate(local_.value(), date, false);
    }

    virtual Double setFullYear(Int year) {
        return setFullYear(local_.value(), year, false);
    }

    virtual Double setHours(Int hour) {
        return setHours(local_.value(), hour, false);
    }

    virtual Double setMilliseconds(Int ms) {
        return setMilliseconds(local_.value(), ms, false);
    }

    virtual Double setMinutes(Int min) {
        return setMinutes(local_.value(), min, false);
    }

    virtual Double setMonth(Int month) {
        return setMonth(local_.value(), month, false);
    }

    virtual Double setSeconds(Int sec) {
        return setSeconds(local_.value(), sec, false);
    }

    virtual Double setTime(Double value) {
        return set(value);
    }

    virtual Double setUTCDate(Int date) {
        return setDate(utc_.value(), date, true);
    }

    virtual Double setUTCFullYear(Int year) {
        return setFullYear(utc_.value(), year, true);
    }

    virtual Double setUTCHours(Int hour) {
        return setHours(utc_.value(), hour, true);
    }

    virtual Double setUTCMilliseconds(Int ms) {
        return setMilliseconds(utc_.value(), ms, true);
    }

    virtual Double setUTCMinutes(Int min) {
        return setMinutes(utc_.value(), min, true);
    }

    virtual Double setUTCMonth(Int month) {
        return setMonth(utc_.value(), month, true);
    }

    virtual Double setUTCSeconds(Int sec) {
        return setSeconds(utc_.value(), sec, true);
    }

    virtual String::CPtr toDateString() const {
        LIBJ_STATIC_SYMBOL_DEF(symInvalidDate, "Invalid Date");

        if (!local_.IsValid()) return symInvalidDate;

        char buf[20];
        Int num = snprintf(
            buf,
            sizeof(buf) - 1,
            "%3s %3s %02d %4d",
            local_.WeekDayString(),
            local_.MonthString(),
            local_.date(),
            local_.year());
        return String::create(buf, String::UTF8, num);
    }

    virtual String::CPtr toISOString() const {
        LIBJ_STATIC_SYMBOL_DEF(symInvalidDate, "Invalid Date");

        if (!utc_.IsValid()) return symInvalidDate;

        char buf[30];
        Int num = snprintf(
            buf,
            sizeof(buf) - 1,
            "%4d-%02d-%02dT%02d:%02d:%02d.%03dZ",
            utc_.year(),
            utc_.month() + 1,
            utc_.date(),
            utc_.hour(),
            utc_.min(),
            utc_.sec(),
            utc_.ms());
        return String::create(buf, String::UTF8, num);
    }

    virtual String::CPtr toJSON() const {
        LIBJ_STATIC_SYMBOL_DEF(symNaNDate, "\"NaN-NaN-NaNTNaN:NaN:NaNZ\"");

        if (!utc_.IsValid()) return symNaNDate;

        char buf[30];
        Int num = snprintf(
            buf,
            sizeof(buf) - 1,
            "\"%4d-%02d-%02dT%02d:%02d:%02dZ\"",
            utc_.year(),
            utc_.month() + 1,
            utc_.date(),
            utc_.hour(),
            utc_.min(),
            utc_.sec());
        return String::create(buf, String::UTF8, num);
    }

    virtual String::CPtr toString() const {
        LIBJ_STATIC_SYMBOL_DEF(symInvalidDate, "Invalid Date");

        if (!local_.IsValid()) return symInvalidDate;

        char sign = (timezone_ > 0) ? '-' : '+';
        Int offset = (timezone_ > 0) ? timezone_ : -timezone_;
        Int tzMin = offset % 60;
        Int tzHour = offset / 60;

        char buf[40];
        Int num = snprintf(
            buf,
            sizeof(buf) - 1,
            "%3s %3s %02d %4d %02d:%02d:%02d GMT%c%02d%02d",
            local_.WeekDayString(),
            local_.MonthString(),
            local_.date(),
            local_.year(),
            local_.hour(),
            local_.min(),
            local_.sec(),
            sign,
            tzHour,
            tzMin);
        return String::create(buf, String::UTF8, num);
    }

    virtual String::CPtr toTimeString() const {
        LIBJ_STATIC_SYMBOL_DEF(symInvalidDate, "Invalid Date");

        if (!local_.IsValid()) return symInvalidDate;

        char sign = (timezone_ > 0) ? '-' : '+';
        Int offset = (timezone_ > 0) ? timezone_ : -timezone_;
        Int tzMin = offset % 60;
        Int tzHour = offset / 60;

        char buf[20];
        Int num = snprintf(
            buf,
            sizeof(buf) - 1,
            "%02d:%02d:%02d GMT%c%02d%02d",
            local_.hour(),
            local_.min(),
            local_.sec(),
            sign,
            tzHour,
            tzMin);
        return String::create(buf, String::UTF8, num);
    }

    virtual String::CPtr toUTCString() const {
        LIBJ_STATIC_SYMBOL_DEF(symInvalidDate, "Invalid Date");

        if (!utc_.IsValid()) return symInvalidDate;

        char buf[40];
        Int num = snprintf(
            buf,
            sizeof(buf) - 1,
            "%3s, %02d %3s %4d %02d:%02d:%02d GMT",
            utc_.WeekDayString(),
            utc_.date(),
            utc_.MonthString(),
            utc_.year(),
            utc_.hour(),
            utc_.min(),
            utc_.sec());
        return String::create(buf, String::UTF8, num);
    }

 private:
    Double set(Double value) {
        Double utc = iv::core::date::TimeClip(value);
        Double local = iv::core::date::LocalTime(utc);

        utc_.SetValue(utc);
        local_.SetValue(local);

        Int diff = static_cast<Int>(utc - local);
        timezone_ = diff / iv::core::date::kMsPerMinute;
        return utc;
    }

    Double setDate(Double value, Int date, Boolean utc) {
        value = iv::core::date::MakeDate(
                    iv::core::date::MakeDay(
                        iv::core::date::YearFromTime(value),
                        iv::core::date::MonthFromTime(value),
                        date),
                    iv::core::date::TimeWithinDay(value));
        if (!utc) value = iv::core::date::UTC(value);
        return set(value);
    }

    Double setFullYear(Double value, Int year, Boolean utc) {
        value = iv::core::date::MakeDate(
                    iv::core::date::MakeDay(
                        year,
                        iv::core::date::MonthFromTime(value),
                        iv::core::date::DateFromTime(value)),
                    iv::core::date::TimeWithinDay(value));
        if (!utc) value = iv::core::date::UTC(value);
        return set(value);
    }

    Double setHours(Double value, Int hour, Boolean utc) {
        value = iv::core::date::MakeDate(
                    iv::core::date::Day(value),
                    iv::core::date::MakeTime(
                        hour,
                        iv::core::date::MinFromTime(value),
                        iv::core::date::SecFromTime(value),
                        iv::core::date::MsFromTime(value)));
        if (!utc) value = iv::core::date::UTC(value);
        return set(value);
    }

    Double setMilliseconds(Double value, Int ms, Boolean utc) {
        value = iv::core::date::MakeDate(
                    iv::core::date::Day(value),
                    iv::core::date::MakeTime(
                        iv::core::date::HourFromTime(value),
                        iv::core::date::MinFromTime(value),
                        iv::core::date::SecFromTime(value),
                        ms));
        if (!utc) value = iv::core::date::UTC(value);
        return set(value);
    }

    Double setMinutes(Double value, Int min, Boolean utc) {
        value = iv::core::date::MakeDate(
                    iv::core::date::Day(value),
                    iv::core::date::MakeTime(
                        iv::core::date::HourFromTime(value),
                        min,
                        iv::core::date::SecFromTime(value),
                        iv::core::date::MsFromTime(value)));
        if (!utc) value = iv::core::date::UTC(value);
        return set(value);
    }

    Double setMonth(Double value, Int month, Boolean utc) {
        value = iv::core::date::MakeDate(
                    iv::core::date::MakeDay(
                        iv::core::date::YearFromTime(value),
                        month,
                        iv::core::date::DateFromTime(value)),
                    iv::core::date::TimeWithinDay(value));
        if (!utc) value = iv::core::date::UTC(value);
        return set(value);
    }

    Double setSeconds(Double value, Int sec, Boolean utc) {
        value = iv::core::date::MakeDate(
                    iv::core::date::Day(value),
                    iv::core::date::MakeTime(
                        iv::core::date::HourFromTime(value),
                        iv::core::date::MinFromTime(value),
                        sec,
                        iv::core::date::MsFromTime(value)));
        if (!utc) value = iv::core::date::UTC(value);
        return set(value);
    }

    iv::core::date::DateInstance utc_;
    iv::core::date::DateInstance local_;
    Int timezone_;
};

}  // namespace detail
}  // namespace libj

#endif  // LIBJ_DETAIL_JS_DATE_H_
