// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/set.h>
#include <libj/string.h>

namespace libj {

TEST(GTestSet, TestCreate) {
    Set::Ptr s = Set::create();
    ASSERT_EQ(s->size(), 0);
}

TEST(GTestSet, TestInstanceOf) {
    Set::Ptr s = Set::create();
    ASSERT_TRUE(s->instanceOf(Type<Set>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Collection>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Object>::id()));
}

TEST(GTestSet, TestSize) {
    Set::Ptr s = Set::create();
    s->add(123);
    ASSERT_EQ(s->size(), 1);
    s->add(456);
    ASSERT_EQ(s->size(), 2);
    s->add(String::create("abc"));
    ASSERT_EQ(s->size(), 3);
    s->add(String::create("edf"));
    ASSERT_EQ(s->size(), 4);
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
    ASSERT_EQ(s->size(), 0);
}

TEST(GTestSet, TestClear) {
    Set::Ptr s = Set::create();
    s->add(5);
    s->clear();
    ASSERT_EQ(s->size(), 0);
}


#ifdef LIBJ_USE_SP
TEST(GTestSet, TestUseCount) {
    Set::CPtr p = Set::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
