// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string.h>

namespace libj {

TEST(GTestString, TestCreate) {
    String::CPtr s1 = String::create("abc", String::ASCII);
    String::CPtr s2 = String::create("abcde", String::ASCII, 3);
    ASSERT_EQ(s1->compareTo(s2), 0);
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
