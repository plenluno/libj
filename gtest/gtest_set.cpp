// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/set.h>

namespace libj {

TEST(GTestSet, TestCreate) {
    Type<Set>::Ptr s = Set::create();
    ASSERT_EQ(s->size(), 0);
}

TEST(GTestSet, TestInstanceOf) {
    Type<Set>::Ptr s = Set::create();
    ASSERT_TRUE(s->instanceOf(Type<Set>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Collection>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(s->instanceOf(Type<Object>::id()));
}

TEST(GTestSet, TestSize) {
    Type<Set>::Ptr s = Set::create();
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
    Type<Set>::Ptr s = Set::create();
    s->add(123);
    s->add(456);
    
    int v1, v2;
    Type<Iterator>::Ptr itr = s->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v1));
    ASSERT_TRUE(v1 == 123 || v1 == 456);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v2));
    ASSERT_TRUE(v1 != v2 && (v2 == 123 || v2 == 456));
    ASSERT_FALSE(itr->hasNext());
}

}  // namespace libj