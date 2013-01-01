// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_array_buffer.h>
#include <libj/js_data_view.h>

namespace libj {

TEST(GTestJsArrayBuffer, TestCreate) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create();
    ASSERT_TRUE(!!a);
    ASSERT_FALSE(a->data());

    a = JsArrayBuffer::create(1);
    ASSERT_TRUE(!!a);
    ASSERT_TRUE(a->data());
}

TEST(GTestJsArrayBuffer, TestByteLength) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(0);
    ASSERT_EQ(0, a->byteLength());

    a = JsArrayBuffer::create(100);
    ASSERT_EQ(100, a->byteLength());
}

TEST(GTestJsArrayBuffer, TestSlice) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(10);
    JsDataView::Ptr d = JsDataView::create(a);
    d->setUint8(5, 7);

    a = a->slice(4, 9);
    d = JsDataView::create(a);
    UByte b;
    ASSERT_TRUE(d->getUint8(1, &b));
    ASSERT_EQ(7, b);
}

}   // namespace libj
