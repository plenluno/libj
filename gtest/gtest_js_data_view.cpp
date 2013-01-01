// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_data_view.h>
#include <libj/string.h>

#include <cstring>

#pragma GCC diagnostic ignored "-Wnarrowing"

namespace libj {

TEST(GTestJsDataView, TestCreate) {
    JsDataView::Ptr d = JsDataView::create();
    ASSERT_TRUE(!!d);

    d = JsDataView::create(1);
    ASSERT_TRUE(!!d);

    JsArrayBuffer::Ptr a = JsArrayBuffer::create(10);
    d = JsDataView::create(a);
    ASSERT_TRUE(!!d);

    d = JsDataView::create(a, 3, 7);
    ASSERT_TRUE(!!d);

    d = JsDataView::create(a, 10, 0);
    ASSERT_TRUE(!!d);

    d = JsDataView::create(JsArrayBuffer::null());
    ASSERT_TRUE(!d);

    d = JsDataView::create(a, 11);
    ASSERT_TRUE(!d);

    d = JsDataView::create(a, 0, 11);
    ASSERT_TRUE(!d);

    d = JsDataView::create(a, 4, 7);
    ASSERT_TRUE(!d);
}

TEST(GTestJsDataView, TestByteLength) {
    JsDataView::Ptr d = JsDataView::create(0);
    ASSERT_EQ(0, d->byteLength());

    d = JsDataView::create(100);
    ASSERT_EQ(100, d->byteLength());

    JsArrayBuffer::Ptr a = JsArrayBuffer::create(10);
    d = JsDataView::create(a);
    ASSERT_EQ(10, d->byteLength());

    d = JsDataView::create(a, 2);
    ASSERT_EQ(8, d->byteLength());

    d = JsDataView::create(a, 2, 5);
    ASSERT_EQ(5, d->byteLength());
}

TEST(GTestJsDataView, TestByteOffset) {
    JsDataView::Ptr d = JsDataView::create(0);
    ASSERT_EQ(0, d->byteOffset());

    d = JsDataView::create(100);
    ASSERT_EQ(0, d->byteOffset());

    JsArrayBuffer::Ptr a = JsArrayBuffer::create(10);
    d = JsDataView::create(a);
    ASSERT_EQ(0, d->byteOffset());

    d = JsDataView::create(a, 2);
    ASSERT_EQ(2, d->byteOffset());

    d = JsDataView::create(a, 2, 5);
    ASSERT_EQ(2, d->byteOffset());
}

TEST(GTestJsDataView, TestInt8) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i < d->byteLength(); i++) {
        Byte v = -5 * i;
        d->setInt8(i, v);
    }
    for (Size i = 0; i < d->byteLength(); i++) {
        Byte v;
        d->getInt8(i, &v);
        ASSERT_EQ(-5 * i, v);
    }
}

TEST(GTestJsDataView, TestUint8) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i < d->byteLength(); i++) {
        UByte v = 10 * i;
        d->setUint8(i, v);
    }
    for (Size i = 0; i < d->byteLength(); i++) {
        UByte v;
        d->getUint8(i, &v);
        ASSERT_EQ(10 * i, v);
    }
}

TEST(GTestJsDataView, TestAlignedInt16) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i + 1 < d->byteLength(); i += 2) {
        Short v = -300 * i;
        d->setInt16(i, v, true);
    }
    for (Size i = 0; i + 1 < d->byteLength(); i += 2) {
        Short v;
        d->getInt16(i, &v, true);
        ASSERT_EQ(-300 * i, v);
    }
    for (Size i = 0; i + 1 < d->byteLength(); i += 2) {
        Short v = -400 * i;
        d->setInt16(i, v, false);
    }
    for (Size i = 0; i + 1 < d->byteLength(); i += 2) {
        Short v;
        d->getInt16(i, &v, false);
        ASSERT_EQ(-400 * i, v);
    }
}

TEST(GTestJsDataView, TestNonAlignedInt16) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        Short v = -300 * i;
        d->setInt16(i, v, true);
    }
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        Short v;
        d->getInt16(i, &v, true);
        ASSERT_EQ(-300 * i, v);
    }
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        Short v = -400 * i;
        d->setInt16(i, v, false);
    }
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        Short v;
        d->getInt16(i, &v, false);
        ASSERT_EQ(-400 * i, v);
    }
}

TEST(GTestJsDataView, TestAlignedUint16) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i < d->byteLength(); i += 2) {
        UShort v = 300 * i;
        d->setUint16(i, v, true);
    }
    for (Size i = 0; i < d->byteLength(); i += 2) {
        UShort v;
        d->getUint16(i, &v, true);
        ASSERT_EQ(300 * i, v);
    }
    for (Size i = 0; i < d->byteLength(); i += 2) {
        UShort v = 400 * i;
        d->setUint16(i, v, false);
    }
    for (Size i = 0; i < d->byteLength(); i += 2) {
        UShort v;
        d->getUint16(i, &v, false);
        ASSERT_EQ(400 * i, v);
    }
}

TEST(GTestJsDataView, TestNonAlignedUint16) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        UShort v = 300 * i;
        d->setUint16(i, v, true);
    }
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        UShort v;
        d->getUint16(i, &v, true);
        ASSERT_EQ(300 * i, v);
    }
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        UShort v = 400 * i;
        d->setUint16(i, v, false);
    }
    for (Size i = 1; i + 1 < d->byteLength(); i += 2) {
        UShort v;
        d->getUint16(i, &v, false);
        ASSERT_EQ(400 * i, v);
    }
}

TEST(GTestJsDataView, TestAlignedInt32) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Int v = -70000 * i;
        d->setInt32(i, v, true);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Int v;
        d->getInt32(i, &v, true);
        ASSERT_EQ(-70000 * i, v);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Int v = -80000 * i;
        d->setInt32(i, v, false);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Int v;
        d->getInt32(i, &v, false);
        ASSERT_EQ(-80000 * i, v);
    }
}

TEST(GTestJsDataView, TestNonAlignedInt32) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size ofs = 1; ofs < 4; ofs++) {
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Int v = -70000 * i;
            d->setInt32(i, v, true);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Int v;
            d->getInt32(i, &v, true);
            ASSERT_EQ(-70000 * i, v);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Int v = -80000 * i;
            d->setInt32(i, v, false);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Int v;
            d->getInt32(i, &v, false);
            ASSERT_EQ(-80000 * i, v);
        }
    }
}

TEST(GTestJsDataView, TestAlignedUint32) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        UInt v = 70000 * i;
        d->setUint32(i, v, true);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        UInt v;
        d->getUint32(i, &v, true);
        ASSERT_EQ(70000 * i, v);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        UInt v = 80000 * i;
        d->setUint32(i, v, false);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        UInt v;
        d->getUint32(i, &v, false);
        ASSERT_EQ(80000 * i, v);
    }
}

TEST(GTestJsDataView, TestNonAlignedUint32) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size ofs = 1; ofs < 4; ofs++) {
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            UInt v = 70000 * i;
            d->setUint32(i, v, true);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            UInt v;
            d->getUint32(i, &v, true);
            ASSERT_EQ(70000 * i, v);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            UInt v = 80000 * i;
            d->setUint32(i, v, false);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            UInt v;
            d->getUint32(i, &v, false);
            ASSERT_EQ(80000 * i, v);
        }
    }
}

TEST(GTestJsDataView, TestAlignedFloat32) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Float v = 1.23f * i;
        d->setFloat32(i, v, true);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Float v;
        d->getFloat32(i, &v, true);
        ASSERT_EQ(1.23f * i, v);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Float v = -45.6f * i;
        d->setFloat32(i, v, false);
    }
    for (Size i = 0; i + 3 < d->byteLength(); i += 4) {
        Float v;
        d->getFloat32(i, &v, false);
        ASSERT_EQ(-45.6f * i, v);
    }
}

TEST(GTestJsDataView, TestNonAlignedFloat32) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size ofs = 1; ofs < 4; ofs++) {
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Float v = 12.3f * i;
            d->setFloat32(i, v, true);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Float v;
            d->getFloat32(i, &v, true);
            ASSERT_EQ(12.3f * i, v);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Float v = -4.56f * i;
            d->setFloat32(i, v, false);
        }
        for (Size i = ofs; i + 3 < d->byteLength(); i += 4) {
            Float v;
            d->getFloat32(i, &v, false);
            ASSERT_EQ(-4.56f * i, v);
        }
    }
}

TEST(GTestJsDataView, TestAlignedFloat64) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size i = 0; i + 7 < d->byteLength(); i += 8) {
        Double v = 1.23 * i;
        d->setFloat64(i, v, true);
    }
    for (Size i = 0; i + 7 < d->byteLength(); i += 8) {
        Double v;
        d->getFloat64(i, &v, true);
        ASSERT_EQ(1.23 * i, v);
    }
    for (Size i = 0; i + 7 < d->byteLength(); i += 8) {
        Double v = -45.6 * i;
        d->setFloat64(i, v, false);
    }
    for (Size i = 0; i + 7 < d->byteLength(); i += 8) {
        Double v;
        d->getFloat64(i, &v, false);
        ASSERT_EQ(-45.6 * i, v);
    }
}

TEST(GTestJsDataView, TestNonAlignedFloat64) {
    JsDataView::Ptr d = JsDataView::create(20);
    for (Size ofs = 1; ofs < 8; ofs++) {
        for (Size i = ofs; i + 7 < d->byteLength(); i += 8) {
            Double v = 12.3 * i;
            d->setFloat64(i, v, true);
        }
        for (Size i = ofs; i + 7 < d->byteLength(); i += 8) {
            Double v;
            d->getFloat64(i, &v, true);
            ASSERT_EQ(12.3 * i, v);
        }
        for (Size i = ofs; i + 7 < d->byteLength(); i += 8) {
            Double v = -4.56 * i;
            d->setFloat64(i, v, false);
        }
        for (Size i = ofs; i + 7 < d->byteLength(); i += 8) {
            Double v;
            d->getFloat64(i, &v, false);
            ASSERT_EQ(-4.56 * i, v);
        }
    }
}

TEST(GTestJsDataView, TestToString) {
    const char c1[] = "This is a ASCII string";
    JsDataView::Ptr a1 = JsDataView::create(strlen(c1));
    for (Size i = 0; i < strlen(c1); i++)
        a1->setInt8(i, c1[i]);
    String::CPtr s1 = a1->toString();
    String::CPtr e1 = String::create(c1);
    ASSERT_TRUE(s1->equals(e1));

    const char c2[] = {
        0x61, 0x62, 0x63,                                       // abc
        0xe3, 0x81, 0x84, 0xe3, 0x82, 0x8d, 0xe3, 0x81, 0xaf,   // いろは
        0x31, 0x32, 0x33, 0x34,                                 // 1234
        0
    };
    JsDataView::Ptr a2 = JsDataView::create(strlen(c2));
    for (Size i = 0; i < strlen(c2); i++)
        a2->setInt8(i, c2[i]);
    String::CPtr s2 = a2->toString();
    String::CPtr e2 = String::create(c2, String::UTF8);
    ASSERT_TRUE(s2->equals(e2));

    const char c3[] = {
        0xe3, 0x83, 0x99, 0xe3, 0x83, 0xbc, 0xe3, 0x82, 0xb3,
        0xe3, 0x83, 0xb3,                                       // ベーコン
        0x6c, 0x65, 0x74, 0x74, 0x75, 0x63, 0x65,               // lettuce
        0xe3, 0x83, 0x88, 0xe3, 0x83, 0x9e, 0xe3, 0x83, 0x88,   // トマト
        0
    };
    JsDataView::Ptr a3 = JsDataView::create(strlen(c3));
    for (Size i = 0; i < strlen(c3); i++)
        a3->setInt8(i, c3[i]);
    String::CPtr s3 = a3->toString();
    String::CPtr e3 = String::create(c3, String::UTF8);
    ASSERT_TRUE(s3->equals(e3));
}

}   // namespace libj
