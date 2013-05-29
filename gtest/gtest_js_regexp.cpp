// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_regexp.h>

namespace libj {

TEST(GTestJsRegExp, TestCreate) {
    JsRegExp::Ptr re = JsRegExp::create(String::create("a+"));
    ASSERT_TRUE(!!re);
}

TEST(GTestJsRegExp, TestGlobal) {
    JsRegExp::Ptr re1 = JsRegExp::create(
        String::create("a+"));
    ASSERT_FALSE(re1->global());

    JsRegExp::Ptr re2 = JsRegExp::create(
        String::create("a+"),
        JsRegExp::GLOBAL);
    ASSERT_TRUE(re2->global());
}

TEST(GTestJsRegExp, TestIgnoreCase) {
    JsRegExp::Ptr re1 = JsRegExp::create(
        String::create("a+"));
    ASSERT_FALSE(re1->ignoreCase());

    JsRegExp::Ptr re2 = JsRegExp::create(
        String::create("a+"),
        JsRegExp::IGNORE_CASE);
    ASSERT_TRUE(re2->ignoreCase());
}

TEST(GTestJsRegExp, TestMultiline) {
    JsRegExp::Ptr re1 = JsRegExp::create(
        String::create("a+"));
    ASSERT_FALSE(re1->multiline());

    JsRegExp::Ptr re2 = JsRegExp::create(
        String::create("a+"),
        JsRegExp::MULTILINE);
    ASSERT_TRUE(re2->multiline());
}

TEST(GTestJsRegExp, TestExec) {
    JsRegExp::Ptr re = JsRegExp::create(String::create("a+(b*)(c)"));

    JsArray::Ptr a = re->exec(String::create("xaacz"));
    ASSERT_EQ(3, a->length());
    ASSERT_TRUE(a->getCPtr<String>(0)->equals(String::create("aac")));
    ASSERT_TRUE(a->getCPtr<String>(1)->equals(String::create()));
    ASSERT_TRUE(a->getCPtr<String>(2)->equals(String::create("c")));
    Int index = -1;
    to<Int>(a->getProperty(String::create("index")), &index);
    ASSERT_EQ(1, index);
    String::CPtr input =
        toCPtr<String>(a->getProperty(String::create("input")));
    ASSERT_TRUE(input->equals(String::create("xaacz")));

    ASSERT_FALSE(re->exec(String::create("bc")));
}

TEST(GTestJsRegExp, TestExec2) {
    JsRegExp::Ptr re =
        JsRegExp::create(String::create("^([0-9]+)\\.([0-9]+)$"));
    JsArray::Ptr a = re->exec(String::create("1.23"));
    ASSERT_EQ(3, a->length());
    ASSERT_TRUE(a->getCPtr<String>(0)->equals(String::create("1.23")));
    ASSERT_TRUE(a->getCPtr<String>(1)->equals(String::create("1")));
    ASSERT_TRUE(a->getCPtr<String>(2)->equals(String::create("23")));
    Int index = -1;
    to<Int>(a->getProperty(String::create("index")), &index);
    ASSERT_EQ(0, index);
    String::CPtr input =
        toCPtr<String>(a->getProperty(String::create("input")));
    ASSERT_TRUE(input->equals(String::create("1.23")));

    ASSERT_FALSE(re->exec(String::create("1x23")));
    ASSERT_FALSE(re->exec(String::create("v1.23")));
}

TEST(GTestJsRegExp, TestLastIndex) {
    JsRegExp::Ptr re =
        JsRegExp::create(String::create("(hi)?"), JsRegExp::GLOBAL);
    ASSERT_EQ(0, re->lastIndex());

    JsArray::Ptr a = re->exec(String::create("hi"));
    ASSERT_EQ(2, a->length());
    ASSERT_TRUE(a->getCPtr<String>(0)->equals(String::create("hi")));
    ASSERT_TRUE(a->getCPtr<String>(1)->equals(String::create("hi")));

    ASSERT_EQ(2, re->lastIndex());
    a = re->exec(String::create("hi"));
    ASSERT_EQ(2, a->length());
    ASSERT_EQ(0, a->getCPtr<String>(0)->length());
    ASSERT_TRUE(a->get(1).isUndefined());

    re->put(String::create("lastIndex"), static_cast<Size>(3));
    ASSERT_EQ(3, re->lastIndex());
    ASSERT_TRUE(!re->exec(String::create("hi")));
    ASSERT_EQ(0, re->lastIndex());
}

}  // namespace libj
