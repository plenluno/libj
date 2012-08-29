// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/set.h>
#include <libj/string.h>

namespace libj {

TEST(GTestSet, TestCreate) {
    Set::Ptr s = Set::create();
    ASSERT_TRUE(s);
}

TEST(GTestSet, TestInstanceOf) {
    Set::Ptr s = Set::create();
    ASSERT_TRUE(s->instanceof(Type<Set>::id()));
    ASSERT_TRUE(s->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(s->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(s->instanceof(Type<Object>::id()));
}

TEST(GTestSet, TestInstanceOf2) {
    Set::CPtr s = Set::create();
    ASSERT_TRUE(s->instanceof(Type<Set>::id()));
    ASSERT_TRUE(s->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(s->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(s->instanceof(Type<Object>::id()));
}

TEST(GTestSet, TestSize) {
    Set::Ptr s = Set::create();
    ASSERT_EQ(0, s->size());
    s->add(123);
    ASSERT_EQ(1, s->size());
    s->add(String::create("abc"));
    ASSERT_EQ(2, s->size());
}

TEST(GTestSet, TestIterator) {
    Set::Ptr s = Set::create();
    s->add(123);
    s->add(456);

    int v1, v2;
    Iterator::Ptr itr = s->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v1));
    ASSERT_TRUE(v1 == 123 || v1 == 456);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v2));
    ASSERT_TRUE(v2 != v1 && (v2 == 123 || v2 == 456));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestSet, TestIterator2) {
    Set::Ptr s = Set::create();
    s->add(String::create("abc"));
    s->add(String::create("edf"));

    Value v1, v2;
    Iterator::Ptr itr = s->iterator();
    ASSERT_TRUE(itr->hasNext());
    v1 = toCPtr<String>(itr->next());
    ASSERT_TRUE(v1.equals(String::create("abc")) ||
                v1.equals(String::create("edf")));
    ASSERT_TRUE(itr->hasNext());
    v2 = toCPtr<String>(itr->next());
    ASSERT_TRUE(!v2.equals(v1) &&
                (v2.equals(String::create("abc")) ||
                 v2.equals(String::create("edf"))));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestSet, TestAdd) {
    Set::Ptr s = Set::create();
    ASSERT_TRUE(s->add(5));
    ASSERT_FALSE(s->add(5));
    ASSERT_TRUE(s->add(String::create("abc")));
    ASSERT_FALSE(s->add(String::create("abc")));
    ASSERT_EQ(2, s->size());
}

TEST(GTestSet, TestContains) {
    Set::Ptr s = Set::create();
    Int i = 5;
    String::CPtr str = String::create("abc");

    s->add(i);
    s->add(str);
    ASSERT_TRUE(s->contains(i));
    ASSERT_TRUE(s->contains(String::create("abc")));
    ASSERT_FALSE(s->contains(6));
    ASSERT_FALSE(s->contains(String::create("edf")));
}

TEST(GTestSet, TestRemove) {
    Set::Ptr s = Set::create();
    Int i = 5;
    String::CPtr str = String::create("abc");

    s->add(i);
    s->add(str);
    ASSERT_EQ(2, s->size());
    ASSERT_FALSE(s->remove(6));
    ASSERT_FALSE(s->remove(String::create("edf")));
    ASSERT_TRUE(s->remove(i));
    ASSERT_TRUE(s->remove(String::create("abc")));
    ASSERT_EQ(0, s->size());
}

TEST(GTestSet, TestClear) {
    Set::Ptr s = Set::create();
    s->add(5);
    s->add(String::create("abc"));
    s->clear();
    ASSERT_TRUE(s->isEmpty());
}

TEST(GTestSet, TestIsEmpty) {
    Set::Ptr s = Set::create();
    ASSERT_TRUE(s->isEmpty());
    s->add(5);
    ASSERT_FALSE(s->isEmpty());
}

TEST(GTestSet, TestAddAll) {
    Set::Ptr s1 = Set::create();
    s1->add(3);
    s1->add(5);

    Set::Ptr s2 = Set::create();
    s2->add(5);
    s2->add(7);

    ASSERT_TRUE(s1->addAll(s2));
    ASSERT_EQ(3, s1->size());
    ASSERT_TRUE(s1->contains(3));
    ASSERT_TRUE(s1->contains(5));
    ASSERT_TRUE(s1->contains(7));

    ASSERT_FALSE(s1->addAll(Set::null()));
    ASSERT_FALSE(s1->addAll(Set::create()));
}

TEST(GTestSet, TestContainsAll) {
    Set::Ptr s1 = Set::create();
    s1->add(3);
    s1->add(5);

    Set::Ptr s2 = Set::create();
    s2->add(5);

    Set::Ptr s3 = Set::create();
    s3->add(5);
    s3->add(7);

    ASSERT_TRUE(s1->containsAll(s2));
    ASSERT_FALSE(s1->containsAll(s3));
    ASSERT_FALSE(s1->containsAll(Set::null()));
    ASSERT_TRUE(s1->containsAll(Set::create()));
}

TEST(GTestSet, TestRemoveAll) {
    Set::Ptr s1 = Set::create();
    s1->add(3);
    s1->add(5);

    Set::Ptr s2 = Set::create();
    s2->add(5);
    s2->add(7);

    ASSERT_TRUE(s1->removeAll(s2));
    ASSERT_EQ(1, s1->size());
    ASSERT_TRUE(s1->contains(3));

    ASSERT_FALSE(s1->removeAll(Set::null()));
    ASSERT_FALSE(s1->removeAll(Set::create()));
}

TEST(GTestSet, TestRetainAll) {
    Set::Ptr s1 = Set::create();
    s1->add(3);
    s1->add(5);

    Set::Ptr s2 = Set::create();
    s2->add(5);
    s2->add(7);

    ASSERT_TRUE(s1->retainAll(s2));
    ASSERT_EQ(1, s1->size());
    ASSERT_TRUE(s1->contains(5));

    ASSERT_FALSE(s1->retainAll(Set::null()));

    ASSERT_TRUE(s1->retainAll(Set::create()));
    ASSERT_TRUE(s1->isEmpty());
}

#ifdef LIBJ_USE_SP
TEST(GTestSet, TestUseCount) {
    Set::CPtr p = Set::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
