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

TEST(GTestSet, TestSize) {
    Set::Ptr s = Set::create();
    s->add(123);
    ASSERT_EQ(1, s->size());
    s->add(456);
    ASSERT_EQ(2, s->size());
    s->add(String::create("abc"));
    ASSERT_EQ(3, s->size());
    s->add(String::create("edf"));
    ASSERT_EQ(4, s->size());
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
    ASSERT_TRUE(v1 != v2 && (v2 == 123 || v2 == 456));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestSet, TestRemove) {
    Set::Ptr s = Set::create();
    Int i = 5;
    s->add(i);
    s->remove(i);
    ASSERT_EQ(0, s->size());
}

TEST(GTestSet, TestClear) {
    Set::Ptr s = Set::create();
    s->add(5);
    s->clear();
    ASSERT_EQ(0, s->size());
}

#ifdef LIBJ_USE_SP
TEST(GTestSet, TestUseCount) {
    Set::CPtr p = Set::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
