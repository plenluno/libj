// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_array_buffer.h>
#include <libj/error.h>
#include <libj/string.h>
#include <cstring>

#pragma GCC diagnostic ignored "-Wnarrowing"

namespace libj {

TEST(GTestJsArrayBuffer, TestCreate) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create();
    ASSERT_TRUE(a);
    ASSERT_FALSE(a->data());

    a = JsArrayBuffer::create(1);
    ASSERT_TRUE(a);
    ASSERT_TRUE(a->data());
}

TEST(GTestJsArrayBuffer, TestIsEmpty) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create();
    ASSERT_TRUE(a->isEmpty());

    a = JsArrayBuffer::create(1);
    ASSERT_FALSE(a->isEmpty());
}

TEST(GTestJsArrayBuffer, TestSize) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(0);
    ASSERT_EQ(0, a->length());
    a = JsArrayBuffer::create(100);
    ASSERT_EQ(100, a->length());
}

TEST(GTestJsArrayBuffer, TestInt8) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i < a->length(); i++) {
        Byte v = -5 * i;
        a->setInt8(i, v);
    }
    for (Size i = 0; i < a->length(); i++) {
        Byte v;
        a->getInt8(i, &v);
        ASSERT_EQ(-5 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestUInt8) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i < a->length(); i++) {
        UByte v = 10 * i;
        a->setUInt8(i, v);
    }
    for (Size i = 0; i < a->length(); i++) {
        UByte v;
        a->getUInt8(i, &v);
        ASSERT_EQ(10 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestAlignedInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i + 1 < a->length(); i += 2) {
        Short v = -300 * i;
        a->setInt16(i, v, true);
    }
    for (Size i = 0; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, true);
        ASSERT_EQ(-300 * i, v);
    }
    for (Size i = 0; i + 1 < a->length(); i += 2) {
        Short v = -400 * i;
        a->setInt16(i, v, false);
    }
    for (Size i = 0; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, false);
        ASSERT_EQ(-400 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        Short v = -300 * i;
        a->setInt16(i, v, true);
    }
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, true);
        ASSERT_EQ(-300 * i, v);
    }
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        Short v = -400 * i;
        a->setInt16(i, v, false);
    }
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, false);
        ASSERT_EQ(-400 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestAlignedUInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i < a->length(); i += 2) {
        UShort v = 300 * i;
        a->setUInt16(i, v, true);
    }
    for (Size i = 0; i < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, true);
        ASSERT_EQ(300 * i, v);
    }
    for (Size i = 0; i < a->length(); i += 2) {
        UShort v = 400 * i;
        a->setUInt16(i, v, false);
    }
    for (Size i = 0; i < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, false);
        ASSERT_EQ(400 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedUInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        UShort v = 300 * i;
        a->setUInt16(i, v, true);
    }
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, true);
        ASSERT_EQ(300 * i, v);
    }
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        UShort v = 400 * i;
        a->setUInt16(i, v, false);
    }
    for (Size i = 1; i + 1 < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, false);
        ASSERT_EQ(400 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestAlignedInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Int v = -70000 * i;
        a->setInt32(i, v, true);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Int v;
        a->getInt32(i, &v, true);
        ASSERT_EQ(-70000 * i, v);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Int v = -80000 * i;
        a->setInt32(i, v, false);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Int v;
        a->getInt32(i, &v, false);
        ASSERT_EQ(-80000 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size ofs = 1; ofs < 4; ofs++) {
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Int v = -70000 * i;
            a->setInt32(i, v, true);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Int v;
            a->getInt32(i, &v, true);
            ASSERT_EQ(-70000 * i, v);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Int v = -80000 * i;
            a->setInt32(i, v, false);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Int v;
            a->getInt32(i, &v, false);
            ASSERT_EQ(-80000 * i, v);
        }
    }
}

TEST(GTestJsArrayBuffer, TestAlignedUInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        UInt v = 70000 * i;
        a->setUInt32(i, v, true);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        UInt v;
        a->getUInt32(i, &v, true);
        ASSERT_EQ(70000 * i, v);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        UInt v = 80000 * i;
        a->setUInt32(i, v, false);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        UInt v;
        a->getUInt32(i, &v, false);
        ASSERT_EQ(80000 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedUInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size ofs = 1; ofs < 4; ofs++) {
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            UInt v = 70000 * i;
            a->setUInt32(i, v, true);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            UInt v;
            a->getUInt32(i, &v, true);
            ASSERT_EQ(70000 * i, v);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            UInt v = 80000 * i;
            a->setUInt32(i, v, false);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            UInt v;
            a->getUInt32(i, &v, false);
            ASSERT_EQ(80000 * i, v);
        }
    }
}

TEST(GTestJsArrayBuffer, TestAlignedFloat32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Float v = 1.23f * i;
        a->setFloat32(i, v, true);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Float v;
        a->getFloat32(i, &v, true);
        ASSERT_EQ(1.23f * i, v);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Float v = -45.6f * i;
        a->setFloat32(i, v, false);
    }
    for (Size i = 0; i + 3 < a->length(); i += 4) {
        Float v;
        a->getFloat32(i, &v, false);
        ASSERT_EQ(-45.6f * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedFloat32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size ofs = 1; ofs < 4; ofs++) {
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Float v = 12.3f * i;
            a->setFloat32(i, v, true);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Float v;
            a->getFloat32(i, &v, true);
            ASSERT_EQ(12.3f * i, v);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Float v = -4.56f * i;
            a->setFloat32(i, v, false);
        }
        for (Size i = ofs; i + 3 < a->length(); i += 4) {
            Float v;
            a->getFloat32(i, &v, false);
            ASSERT_EQ(-4.56f * i, v);
        }
    }
}

TEST(GTestJsArrayBuffer, TestAlignedFloat64) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size i = 0; i + 7 < a->length(); i += 8) {
        Double v = 1.23 * i;
        a->setFloat64(i, v, true);
    }
    for (Size i = 0; i + 7 < a->length(); i += 8) {
        Double v;
        a->getFloat64(i, &v, true);
        ASSERT_EQ(1.23 * i, v);
    }
    for (Size i = 0; i + 7 < a->length(); i += 8) {
        Double v = -45.6 * i;
        a->setFloat64(i, v, false);
    }
    for (Size i = 0; i + 7 < a->length(); i += 8) {
        Double v;
        a->getFloat64(i, &v, false);
        ASSERT_EQ(-45.6 * i, v);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedFloat64) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (Size ofs = 1; ofs < 8; ofs++) {
        for (Size i = ofs; i + 7 < a->length(); i += 8) {
            Double v = 12.3 * i;
            a->setFloat64(i, v, true);
        }
        for (Size i = ofs; i + 7 < a->length(); i += 8) {
            Double v;
            a->getFloat64(i, &v, true);
            ASSERT_EQ(12.3 * i, v);
        }
        for (Size i = ofs; i + 7 < a->length(); i += 8) {
            Double v = -4.56 * i;
            a->setFloat64(i, v, false);
        }
        for (Size i = ofs; i + 7 < a->length(); i += 8) {
            Double v;
            a->getFloat64(i, &v, false);
            ASSERT_EQ(-4.56 * i, v);
        }
    }
}

TEST(GTestJsArrayBuffer, TestToString) {
    const char c1[] = "This is a ASCII string";
    JsArrayBuffer::Ptr a1 = JsArrayBuffer::create(strlen(c1));
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
    JsArrayBuffer::Ptr a2 = JsArrayBuffer::create(strlen(c2));
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
    JsArrayBuffer::Ptr a3 = JsArrayBuffer::create(strlen(c3));
    for (Size i = 0; i < strlen(c3); i++)
        a3->setInt8(i, c3[i]);
    String::CPtr s3 = a3->toString();
    String::CPtr e3 = String::create(c3, String::UTF8);
    ASSERT_TRUE(s3->equals(e3));
}

}   // namespace libj
