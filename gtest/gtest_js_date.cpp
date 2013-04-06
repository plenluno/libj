// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_date.h>

namespace libj {

TEST(GTestJsDate, TestCreate) {
    JsDate::Ptr d = JsDate::create();
    ASSERT_TRUE(!!d);

    d = JsDate::create(1364685226134);
    ASSERT_TRUE(!!d);
    ASSERT_EQ(1364685226134, d->getTime());

    d = JsDate::create(String::create("Sat, 30 Mar 2013 23:13:46 GMT'"));
    ASSERT_TRUE(!!d);
    ASSERT_EQ(1364685226000, d->getTime());

    d = JsDate::create(2013, 2, 31, 8, 13, 46, 134);
    ASSERT_TRUE(!!d);
    ASSERT_EQ(1364685226134, d->getTime());
}

TEST(GTestJsDate, TestParse) {
    Double v1 = JsDate::parse(
        String::create("Sat, 30 Mar 2013 23:13:46 GMT'"));
    Double v2 = JsDate::parse(
        String::create("Sun Mar 31 2013 08:13:46 GMT+0900 (JST)"));
    ASSERT_EQ(v1, v2);
}

TEST(GTestJsDate, TestGet) {
    // Sat Mar 30 2013 23:13:46 GMT
    // Sun Mar 31 2013 08:13:46 GMT+0900 (JST)
    JsDate::Ptr d = JsDate::create(1364685226134);
    ASSERT_EQ(31,            d->getDate());
    ASSERT_EQ(0,             d->getDay());
    ASSERT_EQ(2013,          d->getFullYear());
    ASSERT_EQ(8,             d->getHours());
    ASSERT_EQ(134,           d->getMilliseconds());
    ASSERT_EQ(13,            d->getMinutes());
    ASSERT_EQ(2,             d->getMonth());
    ASSERT_EQ(46,            d->getSeconds());
    ASSERT_EQ(1364685226134, d->getTime());
    ASSERT_EQ(-540,          d->getTimezoneOffset());
    ASSERT_EQ(30,            d->getUTCDate());
    ASSERT_EQ(6,             d->getUTCDay());
    ASSERT_EQ(2013,          d->getUTCFullYear());
    ASSERT_EQ(23,            d->getUTCHours());
    ASSERT_EQ(134,           d->getUTCMilliseconds());
    ASSERT_EQ(13,            d->getUTCMinutes());
    ASSERT_EQ(2,             d->getUTCMonth());
    ASSERT_EQ(46,            d->getUTCSeconds());
}

TEST(GTestJsDate, TestSet) {
    JsDate::Ptr d = JsDate::create(1364685226134);
    ASSERT_EQ(1364598826134, d->setDate(30));
    ASSERT_EQ(1333062826134, d->setFullYear(2012));
    ASSERT_EQ(1333059226134, d->setHours(7));
    ASSERT_EQ(1333059226133, d->setMilliseconds(133));
    ASSERT_EQ(1333059227133, d->setMilliseconds(1133));
    ASSERT_EQ(1333059167133, d->setMinutes(12));
    ASSERT_EQ(1330553567133, d->setMonth(1));
    ASSERT_EQ(1330553565133, d->setSeconds(45));
    ASSERT_EQ(1330639965133, d->setUTCDate(30));
    ASSERT_EQ(1362175965133, d->setUTCFullYear(2013));
    ASSERT_EQ(1362179565133, d->setUTCHours(23));
    ASSERT_EQ(1362179565134, d->setUTCMilliseconds(134));
    ASSERT_EQ(1362179625134, d->setUTCMinutes(13));
    ASSERT_EQ(1362179625134, d->setUTCMonth(2));
    ASSERT_EQ(1362179626134, d->setUTCSeconds(46));
    ASSERT_EQ(1364685226134, d->setTime(1364685226134));
}

TEST(GTestJsDate, TestToString) {
    JsDate::Ptr d = JsDate::create(1364685226134);
    ASSERT_TRUE(d->toString()->equals(
        String::create("Sun Mar 31 2013 08:13:46 GMT+0900")));
    ASSERT_TRUE(d->toDateString()->equals(
        String::create("Sun Mar 31 2013")));
    ASSERT_TRUE(d->toTimeString()->equals(
        String::create("08:13:46 GMT+0900")));
    ASSERT_TRUE(d->toISOString()->equals(
        String::create("2013-03-30T23:13:46.134Z")));
    ASSERT_TRUE(d->toUTCString()->equals(
        String::create("Sat, 30 Mar 2013 23:13:46 GMT")));
    ASSERT_TRUE(d->toJSON()->equals(
        String::create("\"2013-03-30T23:13:46Z\"")));
}

}  // namespace libj
