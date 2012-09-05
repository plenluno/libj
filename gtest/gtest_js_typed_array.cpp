// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_typed_array.h>
#include <libj/typed_array_list.h>

namespace libj {

TEST(GTestJsTypedArray, TestCreate) {
    JsTypedArray<Int>::Ptr a = JsTypedArray<Int>::create();
    ASSERT_TRUE(a);
}

TEST(GTestJsTypedArray, TestAdd) {
    JsTypedArray<Int>::Ptr a = JsTypedArray<Int>::create();
    ASSERT_TRUE(a->add(5));
    ASSERT_FALSE(a->add(5.5));
    ASSERT_TRUE(a->add(7));
    ASSERT_EQ(2, a->length());
}

TEST(GTestJsTypedArray, TestGet) {
    JsTypedArray<Int>::Ptr a = JsTypedArray<Int>::create();
    ASSERT_TRUE(a->add(5));
    ASSERT_TRUE(a->add(7));
    ASSERT_TRUE(a->get(0).equals(5));
    ASSERT_TRUE(a->get(1).equals(7));
}

TEST(GTestJsTypedArray, TestJsProperty) {
    JsTypedArray<Int>::Ptr a = JsTypedArray<Int>::create();
    a->setProperty(String::create("abc"), 7);
    ASSERT_TRUE(a->hasProperty(String::create("abc")));
    ASSERT_TRUE(a->getProperty(String::create("abc")).equals(7));

    a->deleteProperty(String::create("abc"));
    ASSERT_FALSE(a->hasProperty(String::create("abc")));
}

}  // namespace libj
