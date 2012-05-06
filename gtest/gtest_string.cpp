// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/string.h>

namespace libj {

TEST(GTestString, TestCreate) {
    Type<String>::Cptr s1 = String::create("abc", String::ASCII);
    Type<String>::Cptr s2 = String::create("abcde", String::ASCII, 3);
    ASSERT_EQ(s1->compareTo(s2), 0);
}

TEST(GTestString, TestInstanceOf) {
    Type<String>::Cptr s = String::create();
    ASSERT_TRUE(s->instanceOf(Type<String>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Immutable>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Object>::id()));
}

TEST(GTestString, TestLength) {
    Type<String>::Cptr s = String::create();
    ASSERT_EQ(s->length(), 0);

    s = String::create("abc", String::ASCII);
    ASSERT_EQ(s->length(), 3);
}

TEST(GTestString, TestCharAt) {
    Type<String>::Cptr s = String::create("abc", String::ASCII);
    ASSERT_EQ(s->charAt(1), 'b');
    ASSERT_EQ(s->charAt(3), NO_CHAR);
}

TEST(GTestString, TestSubstring) {
    Type<String>::Cptr s = String::create("abcde", String::ASCII);
    Type<String>::Cptr ss1 = s->substring(2);
    Type<String>::Cptr ss2 = s->substring(1, 4);
    Type<String>::Cptr s1 = String::create("cde", String::ASCII);
    Type<String>::Cptr s2 = String::create("bcd", String::ASCII);
    ASSERT_EQ(s1->compareTo(ss1), 0);
    ASSERT_EQ(s2->compareTo(ss2), 0);
}

TEST(GTestString, TestConcat) {
    Type<String>::Cptr s = String::create("abcde", String::ASCII);
    Type<String>::Cptr s1 = String::create("abc", String::ASCII);
    Type<String>::Cptr s2 = String::create("de", String::ASCII);
    ASSERT_EQ(s->compareTo(s1->concat(s2)), 0);
}

TEST(GTestString, TestCompareTo) {
    Type<String>::Cptr a = String::create("a", String::ASCII);
    Type<String>::Cptr c = String::create("c", String::ASCII);
    Type<String>::Cptr abcde = String::create("abcde", String::ASCII);
    ASSERT_EQ(a->compareTo(c), -2);
    ASSERT_EQ(a->compareTo(abcde), -4);
    ASSERT_EQ(abcde->compareTo(c), -2);
    ASSERT_EQ(abcde->compareTo(a), 4);
    ASSERT_EQ(abcde->compareTo(abcde), 0);
    ASSERT_EQ(c->compareTo(a), 2);
    ASSERT_EQ(c->compareTo(abcde), 2);
}

TEST(GTestString, TestStartsWith) {
    Type<String>::Cptr s = String::create("abcde", String::ASCII);
    Type<String>::Cptr s1 = String::create("abc", String::ASCII);
    Type<String>::Cptr s2 = String::create("cd", String::ASCII);
    ASSERT_EQ(s->startsWith(s1), true);
    ASSERT_EQ(s->startsWith(s2), false);
    ASSERT_EQ(s->startsWith(s2, 2), true);
}

TEST(GTestString, TestEndsWith) {
    Type<String>::Cptr s = String::create("abcde", String::ASCII);
    Type<String>::Cptr s1 = String::create("abc", String::ASCII);
    Type<String>::Cptr s2 = String::create("cde", String::ASCII);
    ASSERT_EQ(s->endsWith(s1), false);
    ASSERT_EQ(s->endsWith(s2), true);
}

TEST(GTestString, TestIndexOf) {
    Type<String>::Cptr s = String::create("abcabc", String::ASCII);
    ASSERT_EQ(s->indexOf('b'), 1);
    ASSERT_EQ(s->indexOf('b', 2), 4);
    ASSERT_EQ(s->indexOf('d'), NO_POS);
}

TEST(GTestString, TestIndexOf2) {
    Type<String>::Cptr s = String::create("abcabc", String::ASCII);
    Type<String>::Cptr s1 = String::create("bc", String::ASCII);
    Type<String>::Cptr s2 = String::create("cd", String::ASCII);
    ASSERT_EQ(s->indexOf(s1), 1);
    ASSERT_EQ(s->indexOf(s1, 2), 4);
    ASSERT_EQ(s->indexOf(s2), NO_POS);
}

TEST(GTestString, TestLastIndexOf) {
    Type<String>::Cptr s = String::create("abcabc", String::ASCII);
    ASSERT_EQ(s->lastIndexOf('a'), 3);
    ASSERT_EQ(s->lastIndexOf('a', 2), 0);
    ASSERT_EQ(s->lastIndexOf('d'), NO_POS);
}

TEST(GTestString, TestLastIndexOf2) {
    Type<String>::Cptr s = String::create("abcabc", String::ASCII);
    Type<String>::Cptr s1 = String::create("ab", String::ASCII);
    Type<String>::Cptr s2 = String::create("cd", String::ASCII);
    ASSERT_EQ(s->lastIndexOf(s1), 3);
    ASSERT_EQ(s->lastIndexOf(s1, 2), 0);
    ASSERT_EQ(s->lastIndexOf(s2), NO_POS);
}

TEST(GTestString, TestToLowerCase) {
    Type<String>::Cptr s = String::create("Ab#");
    Type<String>::Cptr e = String::create("ab#");
    ASSERT_EQ(s->toLowerCase()->compareTo(e), 0);
}

TEST(GTestString, TestToUpperCase) {
    Type<String>::Cptr s = String::create("Ab#");
    Type<String>::Cptr e = String::create("AB#");
    ASSERT_EQ(s->toUpperCase()->compareTo(e), 0);
}

TEST(GTestString, TestToString) {
    Type<String>::Cptr s = String::create("abcabc", String::ASCII);
    ASSERT_EQ(s->toString()->compareTo(s), 0);
    
    Type<Object>::Cptr o = s;
    ASSERT_EQ(o->toString()->compareTo(s), 0);
}

TEST(GTestString, TestData) {
    Type<String>::Cptr s = String::create("abcabc", String::ASCII);
    TypeId tid;
    Type<String>::Cptr s2 = String::create(s->data(&tid));
    ASSERT_EQ(tid, Type<char>::id());
    ASSERT_EQ(s->compareTo(s2), 0);
}

}  // namespace libj
