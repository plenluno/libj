// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string.h>

namespace libj {

TEST(GTestString, TestCreate) {
    String::CPtr s1 = String::create("abc", String::ASCII);
    String::CPtr s2 = String::create("abcde", String::ASCII, 3);
    ASSERT_EQ(s1->compareTo(s2), 0);
}

TEST(GTestString, TestCreateUtf) {
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

    const int8_t u8[] = {
        0x01,                   // U+0001
        0x7f,                   // U+007F
        0xc2, 0x80,             // U+0080
        0xdf, 0xbf,             // U+07FF
        0xe0, 0xa0, 0x80,       // U+0800
        0xef, 0xbf, 0xbf,       // U+FFFF
        0xf0, 0x90, 0x80, 0x80, // U+10000
        0xf4, 0x8f, 0xbf, 0xbf  // U+10FFFF
    };
    const int16_t u16[] = {
        0x01, 0x7f, 0x0080, 0x07ff, 0x0800, 0xffff,
        0xd800, 0xdc00, // U+10000
        0xdbff, 0xdfff  // U+10FFFF
    };
    const int32_t u32[] = {
        0x01, 0x7f, 0x0080, 0x07ff, 0x0800, 0xffff, 0x10000, 0x10ffff
    };
    String::CPtr s5 = String::create(u8, String::UTF8);
    String::CPtr s6 = String::create(u16, String::UTF16);
    String::CPtr s7 = String::create(u32, String::UTF32);
    ASSERT_EQ(s5->compareTo(s6), 0);
    ASSERT_EQ(s6->compareTo(s7), 0);
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
    String::CPtr s = String::create("abc123");
    ASSERT_EQ(s->toStdString().compare("abc123"), 0);
}

#ifdef LIBJ_USE_SP
TEST(GTestString, TestUseCount) {
    String::CPtr p = String::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
