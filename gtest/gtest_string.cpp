// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string.h>

#pragma GCC diagnostic ignored "-Wnarrowing"

namespace libj {

TEST(GTestString, TestCreate1) {
    String::CPtr s1 = String::create("abc");
    String::CPtr s2 = String::create("abcde", String::UTF8, 3);
    String::CPtr s3 = String::create("abcde", String::UTF8, NO_SIZE, 3);
    ASSERT_TRUE(s1->equals(s2));
    ASSERT_TRUE(s1->equals(s3));
}

TEST(GTestString, TestCreate2) {
    // single byte characters
    const int8_t  a8[]  = "abcde";
    const int16_t a16be[] = {
        0x6100, 0x6200, 0x6300,
        0x6400, 0x6500, 0x0000
    };
    const int16_t a16le[] = {
        0x0061, 0x0062, 0x0063,
        0x0064, 0x0065, 0x0000
    };
    const int32_t a32be[] = {
        0x61000000, 0x62000000,
        0x63000000, 0x64000000,
        0x65000000, 0x00000000
    };
    const int32_t a32le[] = {
        0x00000061, 0x00000062,
        0x00000063, 0x00000064,
        0x00000065, 0x00000000
    };
    String::CPtr s1 = String::create(a8,    String::UTF8);
    String::CPtr s2 = String::create(a16be, String::UTF16BE);
    String::CPtr s3 = String::create(a16le, String::UTF16LE);
    String::CPtr s4 = String::create(a32be, String::UTF32BE);
    String::CPtr s5 = String::create(a32le, String::UTF32LE);
    ASSERT_TRUE(s1->equals(s2));
    ASSERT_TRUE(s2->equals(s3));
    ASSERT_TRUE(s3->equals(s4));
    ASSERT_TRUE(s4->equals(s5));
    ASSERT_TRUE(s5->equals(s1));
}

TEST(GTestString, TestCreateUtf1) {
    // multi byte characters
    const int8_t u8[] = {
        0x01,                    // U+0001
        0x7f,                    // U+007F
        0xc2, 0x80,              // U+0080
        0xdf, 0xbf,              // U+07FF
        0xe0, 0xa0, 0x80,        // U+0800
        0xef, 0xbf, 0xbf,        // U+FFFF
        0xf0, 0x90, 0x80, 0x80,  // U+10000
        0xf4, 0x8f, 0xbf, 0xbf,  // U+10FFFF
        0x00                     // U+0000 (end of string)
    };
    const int16_t u16be[] = {
        0x0100, 0x7f00, 0x8000, 0xff07, 0x0008, 0xffff,
        0x00d8, 0x00dc,  // U+10000
        0xffdb, 0xffdf,  // U+10FFFF
        0x0000           // U+0000 (end of string)
    };
    const int16_t u16le[] = {
        0x0001, 0x007f, 0x0080, 0x07ff, 0x0800, 0xffff,
        0xd800, 0xdc00,  // U+10000
        0xdbff, 0xdfff,  // U+10FFFF
        0x0000           // U+0000 (end of string)
    };
    const int32_t u32be[] = {
        0x01000000, 0x7f000000, 0x80000000, 0xff070000,
        0x00080000, 0xffff0000, 0x00000100, 0xffff1000,
        0x00000000
    };
    const int32_t u32le[] = {
        0x00000001, 0x0000007f, 0x00000080, 0x000007ff,
        0x00000800, 0x0000ffff, 0x00010000, 0x0010ffff,
        0
    };
    String::CPtr s1 = String::create(u8,    String::UTF8);
    String::CPtr s2 = String::create(u16be, String::UTF16BE);
    String::CPtr s3 = String::create(u16le, String::UTF16LE);
    String::CPtr s4 = String::create(u32be, String::UTF32BE);
    String::CPtr s5 = String::create(u32le, String::UTF32LE);
    ASSERT_TRUE(s1->equals(s2));
    ASSERT_TRUE(s2->equals(s3));
    ASSERT_TRUE(s3->equals(s4));
    ASSERT_TRUE(s4->equals(s5));
    ASSERT_TRUE(s5->equals(s1));

    ASSERT_EQ(0, String::create(u8, String::UTF8, 0)->length());
    ASSERT_EQ(1, String::create(u8, String::UTF8, 1)->length());
    ASSERT_EQ(2, String::create(u8, String::UTF8, 2)->length());
    ASSERT_EQ(2, String::create(u8, String::UTF8, 3)->length());
    ASSERT_EQ(3, String::create(u8, String::UTF8, 4)->length());

#ifdef LIBJ_USE_UTF16
    ASSERT_EQ(6, String::create(u16be, String::UTF16BE, 6)->length());
    ASSERT_EQ(6, String::create(u16be, String::UTF16BE, 7)->length());
    ASSERT_EQ(8, String::create(u16be, String::UTF16BE, 8)->length());

    ASSERT_EQ(6, String::create(u32le, String::UTF32LE, 6)->length());
    ASSERT_EQ(8, String::create(u32le, String::UTF32LE, 7)->length());
#else
    ASSERT_EQ(6, String::create(u16be, String::UTF16BE, 6)->length());
    ASSERT_EQ(6, String::create(u16be, String::UTF16BE, 7)->length());
    ASSERT_EQ(7, String::create(u16be, String::UTF16BE, 8)->length());

    ASSERT_EQ(6, String::create(u32le, String::UTF32LE, 6)->length());
    ASSERT_EQ(7, String::create(u32le, String::UTF32LE, 7)->length());
#endif

    for (int len = 0; len <= 10; len++) {
        String::CPtr s1 = String::create(u16be, String::UTF16BE, len);
        String::CPtr s2 = String::create(u16le, String::UTF16LE, len);
        ASSERT_TRUE(s1->equals(s2));
    }

    for (int len = 0; len <= 8; len++) {
        String::CPtr s1 = String::create(u32be, String::UTF32BE, len);
        String::CPtr s2 = String::create(u32le, String::UTF32LE, len);
        ASSERT_TRUE(s1->equals(s2));
    }

    for (int len = 0; len <= 8; len++) {
        String::CPtr s1 = String::create(u8,    String::UTF8,    NO_SIZE, len);
        String::CPtr s2 = String::create(u16be, String::UTF16BE, NO_SIZE, len);
        String::CPtr s3 = String::create(u16le, String::UTF16LE, NO_SIZE, len);
        String::CPtr s4 = String::create(u32be, String::UTF32BE, NO_SIZE, len);
        String::CPtr s5 = String::create(u32le, String::UTF32LE, NO_SIZE, len);
        ASSERT_TRUE(s1->equals(s2));
        ASSERT_TRUE(s2->equals(s3));
        ASSERT_TRUE(s3->equals(s4));
        ASSERT_TRUE(s4->equals(s5));
        ASSERT_TRUE(s5->equals(s1));
    }
}

TEST(GTestString, TestCreateUtf2) {
    // convert longer string than internal buffer
    const char u8[] = {
        0xe5, 0xaf, 0xbf, 0xe9, 0x99, 0x90, 0xe7, 0x84,
        0xa1, 0xe3, 0x80, 0x81, 0xe5, 0xaf, 0xbf, 0xe9,
        0x99, 0x90, 0xe7, 0x84, 0xa1, 0x0a, 0xe4, 0xba,
        0x94, 0xe5, 0x8a, 0xab, 0xe3, 0x81, 0xae, 0xe6,
        0x93, 0xa6, 0xe3, 0x82, 0x8a, 0xe5, 0x88, 0x87,
        0xe3, 0x82, 0x8c, 0x0a, 0xe6, 0xb5, 0xb7, 0xe7,
        0xa0, 0x82, 0xe5, 0x88, 0xa9, 0xe6, 0xb0, 0xb4,
        0xe9, 0xad, 0x9a, 0xe3, 0x81, 0xae, 0x0a, 0xe6,
        0xb0, 0xb4, 0xe8, 0xa1, 0x8c, 0xe6, 0x9c, 0xab,
        0x20, 0xe9, 0x9b, 0xb2, 0xe6, 0x9d, 0xa5, 0xe6,
        0x9c, 0xab, 0x20, 0xe9, 0xa2, 0xa8, 0xe6, 0x9d,
        0xa5, 0xe6, 0x9c, 0xab, 0x0a, 0xe9, 0xa3, 0x9f,
        0xe3, 0x81, 0x86, 0xe5, 0xaf, 0x9d, 0xe3, 0x82,
        0x8b, 0xe5, 0x87, 0xa6, 0xe3, 0x81, 0xab, 0xe4,
        0xbd, 0x8f, 0xe3, 0x82, 0x80, 0xe5, 0x87, 0xa6,
        0x0a, 0xe3, 0x82, 0x84, 0xe3, 0x81, 0xb6, 0xe3,
        0x82, 0x89, 0xe5, 0xb0, 0x8f, 0xe8, 0xb7, 0xaf,
        0xe3, 0x81, 0xae, 0xe8, 0x97, 0xaa, 0xe6, 0x9f,
        0x91, 0xe5, 0xad, 0x90, 0x0a, 0xe3, 0x83, 0x91,
        0xe3, 0x82, 0xa4, 0xe3, 0x83, 0x9d, 0xe3, 0x83,
        0x91, 0xe3, 0x82, 0xa4, 0xe3, 0x83, 0x9d, 0x20,
        0xe3, 0x83, 0x91, 0xe3, 0x82, 0xa4, 0xe3, 0x83,
        0x9d, 0xe3, 0x81, 0xae, 0xe3, 0x82, 0xb7, 0xe3,
        0x83, 0xa5, 0xe3, 0x83, 0xbc, 0xe3, 0x83, 0xaa,
        0xe3, 0x83, 0xb3, 0xe3, 0x82, 0xac, 0xe3, 0x83,
        0xb3, 0x0a, 0xe3, 0x82, 0xb7, 0xe3, 0x83, 0xa5,
        0xe3, 0x83, 0xbc, 0xe3, 0x83, 0xaa, 0xe3, 0x83,
        0xb3, 0xe3, 0x82, 0xac, 0xe3, 0x83, 0xb3, 0xe3,
        0x81, 0xae, 0xe3, 0x82, 0xb0, 0xe3, 0x83, 0xbc,
        0xe3, 0x83, 0xaa, 0xe3, 0x83, 0xb3, 0xe3, 0x83,
        0x80, 0xe3, 0x82, 0xa4, 0x0a, 0xe3, 0x82, 0xb0,
        0xe3, 0x83, 0xbc, 0xe3, 0x83, 0xaa, 0xe3, 0x83,
        0xb3, 0xe3, 0x83, 0x80, 0xe3, 0x82, 0xa4, 0xe3,
        0x81, 0xae, 0xe3, 0x83, 0x9d, 0xe3, 0x83, 0xb3,
        0xe3, 0x83, 0x9d, 0xe3, 0x82, 0xb3, 0xe3, 0x83,
        0x94, 0xe3, 0x83, 0xbc, 0xe3, 0x81, 0xae, 0xe3,
        0x83, 0x9d, 0xe3, 0x83, 0xb3, 0xe3, 0x83, 0x9d,
        0xe3, 0x82, 0xb3, 0xe3, 0x83, 0x8a, 0xe3, 0x83,
        0xbc, 0xe3, 0x81, 0xae, 0x0a, 0xe9, 0x95, 0xb7,
        0xe4, 0xb9, 0x85, 0xe5, 0x91, 0xbd, 0xe3, 0x81,
        0xae, 0xe9, 0x95, 0xb7, 0xe5, 0x8a, 0xa9, 0x0a,
        0
    };
    const char16_t u16[] = {
        0x5bff, 0x9650, 0x7121, 0x3001, 0x5bff, 0x9650, 0x7121, 0x000a,
        0x4e94, 0x52ab, 0x306e, 0x64e6, 0x308a, 0x5207, 0x308c, 0x000a,
        0x6d77, 0x7802, 0x5229, 0x6c34, 0x9b5a, 0x306e, 0x000a, 0x6c34,
        0x884c, 0x672b, 0x0020, 0x96f2, 0x6765, 0x672b, 0x0020, 0x98a8,
        0x6765, 0x672b, 0x000a, 0x98df, 0x3046, 0x5bdd, 0x308b, 0x51e6,
        0x306b, 0x4f4f, 0x3080, 0x51e6, 0x000a, 0x3084, 0x3076, 0x3089,
        0x5c0f, 0x8def, 0x306e, 0x85ea, 0x67d1, 0x5b50, 0x000a, 0x30d1,
        0x30a4, 0x30dd, 0x30d1, 0x30a4, 0x30dd, 0x0020, 0x30d1, 0x30a4,
        0x30dd, 0x306e, 0x30b7, 0x30e5, 0x30fc, 0x30ea, 0x30f3, 0x30ac,
        0x30f3, 0x000a, 0x30b7, 0x30e5, 0x30fc, 0x30ea, 0x30f3, 0x30ac,
        0x30f3, 0x306e, 0x30b0, 0x30fc, 0x30ea, 0x30f3, 0x30c0, 0x30a4,
        0x000a, 0x30b0, 0x30fc, 0x30ea, 0x30f3, 0x30c0, 0x30a4, 0x306e,
        0x30dd, 0x30f3, 0x30dd, 0x30b3, 0x30d4, 0x30fc, 0x306e, 0x30dd,
        0x30f3, 0x30dd, 0x30b3, 0x30ca, 0x30fc, 0x306e, 0x000a, 0x9577,
        0x4e45, 0x547d, 0x306e, 0x9577, 0x52a9, 0x000a,
        0
    };
    const char32_t u32[] = {
        0x00005bff, 0x00009650, 0x00007121, 0x00003001,
        0x00005bff, 0x00009650, 0x00007121, 0x0000000a,
        0x00004e94, 0x000052ab, 0x0000306e, 0x000064e6,
        0x0000308a, 0x00005207, 0x0000308c, 0x0000000a,
        0x00006d77, 0x00007802, 0x00005229, 0x00006c34,
        0x00009b5a, 0x0000306e, 0x0000000a, 0x00006c34,
        0x0000884c, 0x0000672b, 0x00000020, 0x000096f2,
        0x00006765, 0x0000672b, 0x00000020, 0x000098a8,
        0x00006765, 0x0000672b, 0x0000000a, 0x000098df,
        0x00003046, 0x00005bdd, 0x0000308b, 0x000051e6,
        0x0000306b, 0x00004f4f, 0x00003080, 0x000051e6,
        0x0000000a, 0x00003084, 0x00003076, 0x00003089,
        0x00005c0f, 0x00008def, 0x0000306e, 0x000085ea,
        0x000067d1, 0x00005b50, 0x0000000a, 0x000030d1,
        0x000030a4, 0x000030dd, 0x000030d1, 0x000030a4,
        0x000030dd, 0x00000020, 0x000030d1, 0x000030a4,
        0x000030dd, 0x0000306e, 0x000030b7, 0x000030e5,
        0x000030fc, 0x000030ea, 0x000030f3, 0x000030ac,
        0x000030f3, 0x0000000a, 0x000030b7, 0x000030e5,
        0x000030fc, 0x000030ea, 0x000030f3, 0x000030ac,
        0x000030f3, 0x0000306e, 0x000030b0, 0x000030fc,
        0x000030ea, 0x000030f3, 0x000030c0, 0x000030a4,
        0x0000000a, 0x000030b0, 0x000030fc, 0x000030ea,
        0x000030f3, 0x000030c0, 0x000030a4, 0x0000306e,
        0x000030dd, 0x000030f3, 0x000030dd, 0x000030b3,
        0x000030d4, 0x000030fc, 0x0000306e, 0x000030dd,
        0x000030f3, 0x000030dd, 0x000030b3, 0x000030ca,
        0x000030fc, 0x0000306e, 0x0000000a, 0x00009577,
        0x00004e45, 0x0000547d, 0x0000306e, 0x00009577,
        0x000052a9, 0x0000000a,
        0
    };
    String::CPtr s1 = String::create(u8, String::UTF8);
    std::u16string s16(u16);
    String::CPtr s2 = String::create(s16);
    std::u32string s32(u32);
    String::CPtr s3 = String::create(s32);
    ASSERT_TRUE(s2->equals(s1));
    ASSERT_TRUE(s3->equals(s1));
}

TEST(GTestString, TestInstanceOf) {
    String::CPtr s = String::create();
    ASSERT_TRUE(s->instanceof(Type<String>::id()));
    ASSERT_TRUE(s->instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(s->instanceof(Type<Object>::id()));
}

TEST(GTestString, TestLength) {
    String::CPtr s = String::create();
    ASSERT_EQ(0, s->length());

    s = String::create("abc");
    ASSERT_EQ(3, s->length());
}

TEST(GTestString, TestCharAt) {
    String::CPtr s = String::create("abc");
    ASSERT_EQ('b', s->charAt(1));
    ASSERT_EQ(NO_CHAR, s->charAt(3));
}

TEST(GTestString, TestSubstring) {
    String::CPtr s = String::create("abcde");
    String::CPtr ss1 = s->substring(2);
    String::CPtr ss2 = s->substring(1, 4);
    String::CPtr ss3 = s->substring(0);
    String::CPtr ss4 = s->substring(4);
    String::CPtr ss5 = s->substring(5);
    String::CPtr s1 = String::create("cde");
    String::CPtr s2 = String::create("bcd");
    String::CPtr s3 = String::create("abcde");
    String::CPtr s4 = String::create("e");
    String::CPtr s5 = String::create();
    ASSERT_TRUE(s1->equals(ss1));
    ASSERT_TRUE(s2->equals(ss2));
    ASSERT_TRUE(s3->equals(ss3));
    ASSERT_TRUE(s4->equals(ss4));
    ASSERT_TRUE(s5->equals(ss5));
}

TEST(GTestString, TestConcat) {
    String::CPtr s = String::create("abcde");
    String::CPtr s1 = String::create("abc");
    String::CPtr s2 = String::create("de");
    ASSERT_TRUE(s->equals(s1->concat(s2)));

    String::CPtr e = String::create();
    ASSERT_TRUE(s->equals(e->concat(s)));
    ASSERT_TRUE(s->equals(s->concat(e)));

    ASSERT_FALSE(s->concat(String::null()));
}

TEST(GTestString, TestCompareTo) {
    String::CPtr a = String::create("a");
    String::CPtr c = String::create("c");
    String::CPtr abcde = String::create("abcde");

    Int r0 = a->compareTo(c);
    Int r1 = c->compareTo(a);
    Int r2 = a->compareTo(abcde);
    Int r3 = abcde->compareTo(a);
    Int r4 = c->compareTo(abcde);
    Int r5 = abcde->compareTo(c);
    Int r6 = abcde->compareTo(abcde);

    ASSERT_GT(0,   r0);
    ASSERT_LT(0,   r1);
    ASSERT_EQ(r0, -r1);
    ASSERT_GT(0,   r2);
    ASSERT_LT(0,   r3);
    ASSERT_EQ(r2, -r3);
    ASSERT_LT(0,   r4);
    ASSERT_GT(0,   r5);
    ASSERT_EQ(r4, -r5);
    ASSERT_EQ(0,   r6);
}

TEST(GTestString, TestEquals) {
    String::CPtr abc = String::create("abc");
    String::CPtr internedAbc = String::intern(abc);
    String::CPtr internedAbc2 = String::intern("abc");
    ASSERT_NE(abc, internedAbc);
    ASSERT_EQ(internedAbc, internedAbc2);
    ASSERT_TRUE(abc->equals(internedAbc));
    ASSERT_TRUE(internedAbc->equals(abc));

    String::CPtr ab = String::create("ab");
    String::CPtr abcd = String::create("abcd");
    ASSERT_FALSE(abc->equals(ab));
    ASSERT_FALSE(abc->equals(abcd));
    ASSERT_FALSE(internedAbc->equals(ab));
    ASSERT_FALSE(internedAbc->equals(abcd));
}

TEST(GTestString, TestIsEmpty) {
    String::CPtr empty = String::create();
    ASSERT_TRUE(empty->isEmpty());

    String::CPtr abc = String::create("abc");
    ASSERT_FALSE(abc->isEmpty());
}

TEST(GTestString, TestIsInterned) {
    String::CPtr empty = String::create();
    ASSERT_TRUE(empty->isInterned());

    String::CPtr abc = String::create("abc");
    ASSERT_FALSE(abc->isInterned());

    String::CPtr internedAbc = String::intern(abc);
    ASSERT_TRUE(internedAbc->isInterned());

    String::CPtr interned123 = String::intern("123");
    ASSERT_TRUE(interned123->isInterned());
}

TEST(GTestString, TestStartsWith) {
    String::CPtr s = String::create("abcde");
    String::CPtr s1 = String::create("abc");
    String::CPtr s2 = String::create("cd");
    ASSERT_TRUE(s->startsWith(s1));
    ASSERT_FALSE(s->startsWith(s2));
    ASSERT_TRUE(s->startsWith(s2, 2));
    ASSERT_FALSE(s->startsWith(String::null()));
}

TEST(GTestString, TestEndsWith) {
    String::CPtr s = String::create("abcde");
    String::CPtr s1 = String::create("abc");
    String::CPtr s2 = String::create("cde");
    ASSERT_FALSE(s->endsWith(s1));
    ASSERT_TRUE(s->endsWith(s2));
}

TEST(GTestString, TestIndexOf) {
    String::CPtr s = String::create("abcabc");
    ASSERT_EQ(1, s->indexOf('b'));
    ASSERT_EQ(4, s->indexOf('b', 2));
    ASSERT_EQ(NO_POS, s->indexOf('d'));
}

TEST(GTestString, TestIndexOf2) {
    String::CPtr s = String::create("abcabc");
    String::CPtr s1 = String::create("bc");
    String::CPtr s2 = String::create("cd");
    ASSERT_EQ(1, s->indexOf(s1));
    ASSERT_EQ(4, s->indexOf(s1, 2));
    ASSERT_EQ(NO_POS, s->indexOf(s2));
}

TEST(GTestString, TestLastIndexOf) {
    String::CPtr s = String::create("abcabc");
    ASSERT_EQ(3, s->lastIndexOf('a'));
    ASSERT_EQ(0, s->lastIndexOf('a', 2));
    ASSERT_EQ(NO_POS, s->lastIndexOf('d'));
}

TEST(GTestString, TestLastIndexOf2) {
    String::CPtr s = String::create("abcabc");
    String::CPtr s1 = String::create("ab");
    String::CPtr s2 = String::create("cd");
    String::CPtr s3 = String::create("abcabc");
    ASSERT_EQ(3, s->lastIndexOf(s1));
    ASSERT_EQ(0, s->lastIndexOf(s1, 2));
    ASSERT_EQ(NO_POS, s->lastIndexOf(s2));
    ASSERT_EQ(0, s->lastIndexOf(s3, 5));
}

TEST(GTestString, TestToLowerCase) {
    String::CPtr s = String::create("Ab#");
    String::CPtr e = String::create("ab#");
    ASSERT_TRUE(s->toLowerCase()->equals(e));
}

TEST(GTestString, TestToUpperCase) {
    String::CPtr s = String::create("Ab#");
    String::CPtr e = String::create("AB#");
    ASSERT_TRUE(s->toUpperCase()->equals(e));
}

TEST(GTestString, TestToString) {
    String::CPtr s = String::create("abcabc");
    ASSERT_TRUE(s->toString()->equals(s));

    Object::CPtr o = s;
    ASSERT_TRUE(o->toString()->equals(s));
}

TEST(GTestString, TestValueOf) {
    Value v;
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("undefined")));

    v = String::null();
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("null")));

    v = false;
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("false")));

    v = static_cast<Byte>(-123);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("-123")));

    v = static_cast<UByte>(123);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("123")));

    v = static_cast<Short>(-12345);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("-12345")));

    v = static_cast<UShort>(12345);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("12345")));

    v = -1234567890;
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("-1234567890")));

    v = static_cast<UInt>(1234567890);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("1234567890")));

    v = static_cast<Long>(-1234567890);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("-1234567890")));

    v = static_cast<ULong>(1234567890);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("1234567890")));

    v = static_cast<Float>(-1.25);
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("-1.25")));

    v = -1.2345;
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("-1.2345")));

    Size size = 1234567890;
    v = size;
    ASSERT_TRUE(String::valueOf(v)->equals(String::create("1234567890")));

    String::CPtr s = String::create("abc");
    v = s;
    ASSERT_TRUE(String::valueOf(v)->equals(s));
}

#include <iostream>

TEST(GTestString, TestToStdString) {
    String::CPtr s1 = String::create();
    ASSERT_EQ(0, s1->toStdString().compare(""));

    String::CPtr s2 = String::create("abc123");
    ASSERT_EQ(0, s2->toStdString().compare("abc123"));

    const char u8[] = {
        // Hello New York.
        // Guten Tag Köln.
        // こんにちは東京。
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x4e, 0x65,
        0x77, 0x20, 0x59, 0x6f, 0x72, 0x6b, 0x2e, 0x0a,
        0x47, 0x75, 0x74, 0x65, 0x6e, 0x20, 0x54, 0x61,
        0x67, 0x20, 0x4b, 0xc3, 0xb6, 0x6c, 0x6e, 0x2e,
        0x0a, 0xe3, 0x81, 0x93, 0xe3, 0x82, 0x93, 0xe3,
        0x81, 0xab, 0xe3, 0x81, 0xa1, 0xe3, 0x81, 0xaf,
        0xe6, 0x9d, 0xb1, 0xe4, 0xba, 0xac, 0xe3, 0x80,
        0x82, 0x0a,
        0
    };
    String::CPtr s3 = String::create(u8, String::UTF8);
    ASSERT_EQ(0, s3->toStdString().compare(u8));

    String::CPtr s4 = String::create(
        s3->toStdString(String::UTF8).c_str(),
        String::UTF8);
    String::CPtr s5 = String::create(
        s3->toStdString(String::UTF16BE).c_str(),
        String::UTF16BE);
    String::CPtr s6 = String::create(
        s3->toStdString(String::UTF16LE).c_str(),
        String::UTF16LE);
    String::CPtr s7 = String::create(
        s3->toStdString(String::UTF32BE).c_str(),
        String::UTF32BE);
    String::CPtr s8 = String::create(
        s3->toStdString(String::UTF32LE).c_str(),
        String::UTF32LE);
    ASSERT_TRUE(s4->equals(s3));
    ASSERT_TRUE(s5->equals(s3));
    ASSERT_TRUE(s6->equals(s3));
    ASSERT_TRUE(s7->equals(s3));
    ASSERT_TRUE(s8->equals(s3));
}

#ifdef LIBJ_USE_SP
TEST(GTestString, TestUseCount) {
    String::CPtr p = String::create("abc");
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
