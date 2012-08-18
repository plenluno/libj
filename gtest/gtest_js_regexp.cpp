// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_regexp.h>
#include <libj/undefined.h>

namespace libj {

TEST(GTestJsRegExp, TestCreate) {
    JsRegExp::Ptr p = JsRegExp::create(String::create("a+"));
    ASSERT_TRUE(p);
}

TEST(GTestJsRegExp, TestGlobal) {
    JsRegExp::Ptr p1 = JsRegExp::create(
        String::create("a+"));
    ASSERT_FALSE(p1->global());
    JsRegExp::Ptr p2 = JsRegExp::create(
        String::create("a+"),
        JsRegExp::GLOBAL);
    ASSERT_TRUE(p2->global());
}

TEST(GTestJsRegExp, TestIgnoreCase) {
    JsRegExp::Ptr p1 = JsRegExp::create(
        String::create("a+"));
    ASSERT_FALSE(p1->ignoreCase());
    JsRegExp::Ptr p2 = JsRegExp::create(
        String::create("a+"),
        JsRegExp::IGNORE_CASE);
    ASSERT_TRUE(p2->ignoreCase());
}

TEST(GTestJsRegExp, TestMultiline) {
    JsRegExp::Ptr p1 = JsRegExp::create(
        String::create("a+"));
    ASSERT_FALSE(p1->multiline());
    JsRegExp::Ptr p2 = JsRegExp::create(
        String::create("a+"),
        JsRegExp::MULTILINE);
    ASSERT_TRUE(p2->multiline());
}

TEST(GTestJsRegExp, TestExec) {
    JsRegExp::Ptr p1 = JsRegExp::create(
        String::create("a+(b*)(c)"));
    JsArray::Ptr a = p1->exec(String::create("xaacz"));
    ASSERT_EQ(3, a->length());
    ASSERT_TRUE(toCPtr<String>(a->get(0))->equals(String::create("aac")));
    ASSERT_TRUE(toCPtr<Undefined>(a->get(1)));
    ASSERT_TRUE(toCPtr<String>(a->get(2))->equals(String::create("c")));
}

}  // namespace libj
