// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_typed_array.h>
#include <libj/typed_array_list.h>

namespace libj {

TEST(GTestJsTypedArray, TestCreate) {
    JsTypedArray<Int>::Ptr a = JsTypedArray<Int>::create();
    ASSERT_TRUE(a);
}

TEST(GTestJsTypedArray, TestAddAndGet) {
    JsTypedArray<Int>::Ptr a = JsTypedArray<Int>::create();
    a->add(5);
    a->add(7);
    Value v = a->get(1);
    Int i;
    to<Int>(v, &i);
    ASSERT_EQ(i, 7);
}

}  // namespace libj
