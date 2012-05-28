// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string.h>

namespace libj {

TEST(GTestString, TestCreate) {
    String::CPtr s1 = String::create("abc", String::ASCII);
    String::CPtr s2 = String::create("abcde", String::ASCII, 3);
    ASSERT_EQ(s1->compareTo(s2), 0);
}

TEST(GTestString, TestCreateUtf0) {
    // single byte characters
    const int8_t  a8[]  = "abcde";
    const int16_t a16[] = {0x61, 0x62, 0x63, 0x64, 0x65, 0};
    const int32_t a32[] = {0x61, 0x62, 0x63, 0x64, 0x65, 0};
    String::CPtr s1 = String::create(a8, String::ASCII);
    String::CPtr s2 = String::create(a8, String::UTF8);
    String::CPtr s3 = String::create(a16, String::UTF16);
    String::CPtr s4 = String::create(a32, String::UTF32);
    ASSERT_EQ(s1->compareTo(s2), 0);
    ASSERT_EQ(s2->compareTo(s3), 0);
    ASSERT_EQ(s3->compareTo(s4), 0);
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
        0                        // U+0000 (end of string)
    };
    const int16_t u16[] = {
        0x01, 0x7f, 0x0080, 0x07ff, 0x0800, 0xffff,
        0xd800, 0xdc00,  // U+10000
        0xdbff, 0xdfff,  // U+10FFFF
        0                // U+0000 (end of string)
    };
    const int32_t u32[] = {
        0x01, 0x7f, 0x0080, 0x07ff, 0x0800, 0xffff, 0x10000, 0x10ffff,
        0
    };
    String::CPtr s1 = String::create(u8, String::UTF8);
    String::CPtr s2 = String::create(u16, String::UTF16);
    String::CPtr s3 = String::create(u32, String::UTF32);
    ASSERT_EQ(s1->compareTo(s2), 0);
    ASSERT_EQ(s2->compareTo(s3), 0);

    // chop at specified position
    for (int len = 0; len <= 8; len++) {
        String::CPtr s1 = String::create(u8, String::UTF8, len);
        String::CPtr s2 = String::create(u16, String::UTF16, len);
        String::CPtr s3 = String::create(u32, String::UTF32, len);
        ASSERT_EQ(s1->compareTo(s2), 0);
        ASSERT_EQ(s2->compareTo(s3), 0);
    }
}

TEST(GTestString, TestCreateUtf2) {
    // convert longer string than internal buffer
    const int8_t u8[] = {
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
    const int16_t u16[] = {
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
    const int32_t u32[] = {
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
    String::CPtr s2 = String::create(u16, String::UTF16);
    String::CPtr s3 = String::create(u32, String::UTF32);
    ASSERT_EQ(s1->compareTo(s2), 0);
    ASSERT_EQ(s2->compareTo(s3), 0);
}

TEST(GTestString, TestInstanceOf) {
    String::CPtr s = String::create();
    ASSERT_TRUE(s->instanceOf(Type<String>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Immutable>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Object>::id()));
}

TEST(GTestString, TestLength) {
    String::CPtr s = String::create();
    ASSERT_EQ(s->length(), 0);

    s = String::create("abc", String::ASCII);
    ASSERT_EQ(s->length(), 3);
}

TEST(GTestString, TestCharAt) {
    String::CPtr s = String::create("abc", String::ASCII);
    ASSERT_EQ(s->charAt(1), 'b');
    ASSERT_EQ(s->charAt(3), NO_CHAR);
}

TEST(GTestString, TestSubstring) {
    String::CPtr s = String::create("abcde", String::ASCII);
    String::CPtr ss1 = s->substring(2);
    String::CPtr ss2 = s->substring(1, 4);
    String::CPtr s1 = String::create("cde", String::ASCII);
    String::CPtr s2 = String::create("bcd", String::ASCII);
    ASSERT_EQ(s1->compareTo(ss1), 0);
    ASSERT_EQ(s2->compareTo(ss2), 0);
}

TEST(GTestString, TestConcat) {
    String::CPtr s = String::create("abcde", String::ASCII);
    String::CPtr s1 = String::create("abc", String::ASCII);
    String::CPtr s2 = String::create("de", String::ASCII);
    ASSERT_EQ(s->compareTo(s1->concat(s2)), 0);

    String::CPtr e = String::create();
    ASSERT_EQ(s->compareTo(e->concat(s)), 0);
    ASSERT_EQ(s->compareTo(s->concat(e)), 0);

    LIBJ_NULL_CPTR(String, n);
    ASSERT_EQ(s->compareTo(s->concat(n)), 0);
}

TEST(GTestString, TestCompareTo) {
    String::CPtr a = String::create("a", String::ASCII);
    String::CPtr c = String::create("c", String::ASCII);
    String::CPtr abcde = String::create("abcde", String::ASCII);
    ASSERT_EQ(a->compareTo(c), -2);
    ASSERT_EQ(a->compareTo(abcde), -4);
    ASSERT_EQ(abcde->compareTo(c), -2);
    ASSERT_EQ(abcde->compareTo(a), 4);
    ASSERT_EQ(abcde->compareTo(abcde), 0);
    ASSERT_EQ(c->compareTo(a), 2);
    ASSERT_EQ(c->compareTo(abcde), 2);
}

TEST(GTestString, TestStartsWith) {
    String::CPtr s = String::create("abcde", String::ASCII);
    String::CPtr s1 = String::create("abc", String::ASCII);
    String::CPtr s2 = String::create("cd", String::ASCII);
    ASSERT_EQ(s->startsWith(s1), true);
    ASSERT_EQ(s->startsWith(s2), false);
    ASSERT_EQ(s->startsWith(s2, 2), true);
}

TEST(GTestString, TestEndsWith) {
    String::CPtr s = String::create("abcde", String::ASCII);
    String::CPtr s1 = String::create("abc", String::ASCII);
    String::CPtr s2 = String::create("cde", String::ASCII);
    ASSERT_EQ(s->endsWith(s1), false);
    ASSERT_EQ(s->endsWith(s2), true);
}

TEST(GTestString, TestIndexOf) {
    String::CPtr s = String::create("abcabc", String::ASCII);
    ASSERT_EQ(s->indexOf('b'), 1);
    ASSERT_EQ(s->indexOf('b', 2), 4);
    ASSERT_EQ(s->indexOf('d'), NO_POS);
}

TEST(GTestString, TestIndexOf2) {
    String::CPtr s = String::create("abcabc", String::ASCII);
    String::CPtr s1 = String::create("bc", String::ASCII);
    String::CPtr s2 = String::create("cd", String::ASCII);
    ASSERT_EQ(s->indexOf(s1), 1);
    ASSERT_EQ(s->indexOf(s1, 2), 4);
    ASSERT_EQ(s->indexOf(s2), NO_POS);
}

TEST(GTestString, TestLastIndexOf) {
    String::CPtr s = String::create("abcabc", String::ASCII);
    ASSERT_EQ(s->lastIndexOf('a'), 3);
    ASSERT_EQ(s->lastIndexOf('a', 2), 0);
    ASSERT_EQ(s->lastIndexOf('d'), NO_POS);
}

TEST(GTestString, TestLastIndexOf2) {
    String::CPtr s = String::create("abcabc", String::ASCII);
    String::CPtr s1 = String::create("ab", String::ASCII);
    String::CPtr s2 = String::create("cd", String::ASCII);
    ASSERT_EQ(s->lastIndexOf(s1), 3);
    ASSERT_EQ(s->lastIndexOf(s1, 2), 0);
    ASSERT_EQ(s->lastIndexOf(s2), NO_POS);
}

TEST(GTestString, TestToLowerCase) {
    String::CPtr s = String::create("Ab#");
    String::CPtr e = String::create("ab#");
    ASSERT_EQ(s->toLowerCase()->compareTo(e), 0);
}

TEST(GTestString, TestToUpperCase) {
    String::CPtr s = String::create("Ab#");
    String::CPtr e = String::create("AB#");
    ASSERT_EQ(s->toUpperCase()->compareTo(e), 0);
}

TEST(GTestString, TestToString) {
    String::CPtr s = String::create("abcabc", String::ASCII);
    ASSERT_EQ(s->toString()->compareTo(s), 0);

    Object::CPtr o = s;
    ASSERT_EQ(o->toString()->compareTo(s), 0);
}

TEST(GTestString, TestValueOf) {
    Value v;
    ASSERT_FALSE(String::valueOf(v));

    LIBJ_NULL_CPTR(String, nullp);
    v = nullp;
    ASSERT_FALSE(String::valueOf(v));

    v = 3;
    ASSERT_EQ(String::valueOf(v)->compareTo(String::create("3")), 0);

    String::CPtr s = String::create("abc");
    v = s;
    ASSERT_EQ(String::valueOf(v)->compareTo(s), 0);
}

TEST(GTestString, TestToStdString) {
    String::CPtr s1 = String::create();
    ASSERT_EQ(s1->toStdString().compare(""), 0);

    String::CPtr s2 = String::create("abc123");
    ASSERT_EQ(s2->toStdString().compare("abc123"), 0);

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
    ASSERT_EQ(s3->toStdString().compare(u8), 0);
}

#ifdef LIBJ_USE_SP
TEST(GTestString, TestUseCount) {
    String::CPtr p = String::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
