// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_array_buffer.h>
#include <libj/error.h>
#include <libj/string.h>
#include <cstring>

namespace libj {

TEST(GTestJsArrayBuffer, TestCreate) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create();
    ASSERT_EQ(a->length(), 0);
}

TEST(GTestJsArrayBuffer, TestSize) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(0);
    ASSERT_EQ(a->length(), 0);
    a = JsArrayBuffer::create(10);
    ASSERT_EQ(a->length(), 10);
    a = JsArrayBuffer::create(100);
    ASSERT_EQ(a->length(), 100);
}

TEST(GTestJsArrayBuffer, TestInt8) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i < a->length(); i++) {
        Byte v = -5 * i;
        a->setInt8(i, v);
    }
    for (int i = 0; i < a->length(); i++) {
        Byte v;
        a->getInt8(i, &v);
        ASSERT_EQ(v, -5 * i);
    }
}

TEST(GTestJsArrayBuffer, TestUInt8) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i < a->length(); i++) {
        UByte v = 10 * i;
        a->setUInt8(i, v);
    }
    for (int i = 0; i < a->length(); i++) {
        UByte v;
        a->getUInt8(i, &v);
        ASSERT_EQ(v, 10 * i);
    }
}

TEST(GTestJsArrayBuffer, TestAlignedInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i + 1 < a->length(); i += 2) {
        Short v = -300 * i;
        a->setInt16(i, v, true);
    }
    for (int i = 0; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, true);
        ASSERT_EQ(v, -300 * i);
    }
    for (int i = 0; i + 1 < a->length(); i += 2) {
        Short v = -400 * i;
        a->setInt16(i, v, false);
    }
    for (int i = 0; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, false);
        ASSERT_EQ(v, -400 * i);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 1; i + 1 < a->length(); i += 2) {
        Short v = -300 * i;
        a->setInt16(i, v, true);
    }
    for (int i = 1; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, true);
        ASSERT_EQ(v, -300 * i);
    }
    for (int i = 1; i + 1 < a->length(); i += 2) {
        Short v = -400 * i;
        a->setInt16(i, v, false);
    }
    for (int i = 1; i + 1 < a->length(); i += 2) {
        Short v;
        a->getInt16(i, &v, false);
        ASSERT_EQ(v, -400 * i);
    }
}

TEST(GTestJsArrayBuffer, TestAlignedUInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i < a->length(); i += 2) {
        UShort v = 300 * i;
        a->setUInt16(i, v, true);
    }
    for (int i = 0; i < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, true);
        ASSERT_EQ(v, 300 * i);
    }
    for (int i = 0; i < a->length(); i += 2) {
        UShort v = 400 * i;
        a->setUInt16(i, v, false);
    }
    for (int i = 0; i < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, false);
        ASSERT_EQ(v, 400 * i);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedUInt16) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 1; i + 1 < a->length(); i += 2) {
        UShort v = 300 * i;
        a->setUInt16(i, v, true);
    }
    for (int i = 1; i + 1 < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, true);
        ASSERT_EQ(v, 300 * i);
    }
    for (int i = 1; i + 1 < a->length(); i += 2) {
        UShort v = 400 * i;
        a->setUInt16(i, v, false);
    }
    for (int i = 1; i + 1 < a->length(); i += 2) {
        UShort v;
        a->getUInt16(i, &v, false);
        ASSERT_EQ(v, 400 * i);
    }
}

TEST(GTestJsArrayBuffer, TestAlignedInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Int v = -70000 * i;
        a->setInt32(i, v, true);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Int v;
        a->getInt32(i, &v, true);
        ASSERT_EQ(v, -70000 * i);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Int v = -80000 * i;
        a->setInt32(i, v, false);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Int v;
        a->getInt32(i, &v, false);
        ASSERT_EQ(v, -80000 * i);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int ofs = 1; ofs < 4; ofs++) {
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Int v = -70000 * i;
            a->setInt32(i, v, true);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Int v;
            a->getInt32(i, &v, true);
            ASSERT_EQ(v, -70000 * i);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Int v = -80000 * i;
            a->setInt32(i, v, false);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Int v;
            a->getInt32(i, &v, false);
            ASSERT_EQ(v, -80000 * i);
        }
    }
}

TEST(GTestJsArrayBuffer, TestAlignedUInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i + 3 < a->length(); i += 4) {
        UInt v = 70000 * i;
        a->setUInt32(i, v, true);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        UInt v;
        a->getUInt32(i, &v, true);
        ASSERT_EQ(v, 70000 * i);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        UInt v = 80000 * i;
        a->setUInt32(i, v, false);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        UInt v;
        a->getUInt32(i, &v, false);
        ASSERT_EQ(v, 80000 * i);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedUInt32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int ofs = 1; ofs < 4; ofs++) {
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            UInt v = 70000 * i;
            a->setUInt32(i, v, true);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            UInt v;
            a->getUInt32(i, &v, true);
            ASSERT_EQ(v, 70000 * i);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            UInt v = 80000 * i;
            a->setUInt32(i, v, false);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            UInt v;
            a->getUInt32(i, &v, false);
            ASSERT_EQ(v, 80000 * i);
        }
    }
}

TEST(GTestJsArrayBuffer, TestAlignedFloat32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Float v = 1.23f * i;
        a->setFloat32(i, v, true);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Float v;
        a->getFloat32(i, &v, true);
        ASSERT_EQ(v, 1.23f * i);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Float v = -45.6f * i;
        a->setFloat32(i, v, false);
    }
    for (int i = 0; i + 3 < a->length(); i += 4) {
        Float v;
        a->getFloat32(i, &v, false);
        ASSERT_EQ(v, -45.6f * i);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedFloat32) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int ofs = 1; ofs < 4; ofs++) {
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Float v = 12.3f * i;
            a->setFloat32(i, v, true);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Float v;
            a->getFloat32(i, &v, true);
            ASSERT_EQ(v, 12.3f * i);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Float v = -4.56f * i;
            a->setFloat32(i, v, false);
        }
        for (int i = ofs; i + 3 < a->length(); i += 4) {
            Float v;
            a->getFloat32(i, &v, false);
            ASSERT_EQ(v, -4.56f * i);
        }
    }
}

TEST(GTestJsArrayBuffer, TestAlignedFloat64) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int i = 0; i + 7 < a->length(); i += 8) {
        Double v = 1.23 * i;
        a->setFloat64(i, v, true);
    }
    for (int i = 0; i + 7 < a->length(); i += 8) {
        Double v;
        a->getFloat64(i, &v, true);
        ASSERT_EQ(v, 1.23 * i);
    }
    for (int i = 0; i + 7 < a->length(); i += 8) {
        Double v = -45.6 * i;
        a->setFloat64(i, v, false);
    }
    for (int i = 0; i + 7 < a->length(); i += 8) {
        Double v;
        a->getFloat64(i, &v, false);
        ASSERT_EQ(v, -45.6 * i);
    }
}

TEST(GTestJsArrayBuffer, TestNonAlignedFloat64) {
    JsArrayBuffer::Ptr a = JsArrayBuffer::create(20);
    for (int ofs = 1; ofs < 8; ofs++) {
        for (int i = ofs; i + 7 < a->length(); i += 8) {
            Double v = 12.3 * i;
            a->setFloat64(i, v, true);
        }
        for (int i = ofs; i + 7 < a->length(); i += 8) {
            Double v;
            a->getFloat64(i, &v, true);
            ASSERT_EQ(v, 12.3 * i);
        }
        for (int i = ofs; i + 7 < a->length(); i += 8) {
            Double v = -4.56 * i;
            a->setFloat64(i, v, false);
        }
        for (int i = ofs; i + 7 < a->length(); i += 8) {
            Double v;
            a->getFloat64(i, &v, false);
            ASSERT_EQ(v, -4.56 * i);
        }
    }
}

TEST(GTestJsArrayBuffer, TestToString) {
    const char c1[] = "This is a ASCII string";
    JsArrayBuffer::Ptr a1 = JsArrayBuffer::create(strlen(c1));
    for (int i = 0; i < strlen(c1); i++)
        a1->setInt8(i, c1[i]);
    String::CPtr s1 = a1->toString();
    String::CPtr e1 = String::create(c1);
    ASSERT_EQ(s1->compareTo(e1), 0);
    ASSERT_TRUE(s1->isAscii());

    const char c2[] = {
        0x61, 0x62, 0x63,                                       // abc
        0xe3, 0x81, 0x84, 0xe3, 0x82, 0x8d, 0xe3, 0x81, 0xaf,   // いろは
        0x31, 0x32, 0x33, 0x34,                                 // 1234
        0
    };
    JsArrayBuffer::Ptr a2 = JsArrayBuffer::create(strlen(c2));
    for (int i = 0; i < strlen(c2); i++)
        a2->setInt8(i, c2[i]);
    String::CPtr s2 = a2->toString();
    String::CPtr e2 = String::create(c2, String::UTF8);
    ASSERT_EQ(s2->compareTo(e2), 0);
    ASSERT_FALSE(s2->isAscii());
}

}   // namespace libj
