// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/array_list.h>
#include <libj/error.h>

namespace libj {

TEST(GTestArrayList, TestCreate) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    ASSERT_EQ(a->size(), 0);
}

TEST(GTestArrayList, TestInstanceOf) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    ASSERT_TRUE(a->instanceOf(Type<ArrayList>::id()));
    ASSERT_TRUE(a->instanceOf(Type<List>::id()));
    ASSERT_TRUE(a->instanceOf(Type<Collection>::id()));
    ASSERT_TRUE(a->instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceOf(Type<Object>::id()));
}

TEST(GTestArrayList, TestSize) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(123);
    ASSERT_EQ(a->size(), 1);
    a->add(456);
    ASSERT_EQ(a->size(), 2);
}

TEST(GTestArrayList, TestAddAndGet) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->add(1, 789);
    
    int v;
    to<int>(a->get(0), &v);
    ASSERT_EQ(v, 123);
    to<int>(a->get(1), &v);
    ASSERT_EQ(v, 789);
    to<int>(a->get(2), &v);
    ASSERT_EQ(v, 456);
}

TEST(GTestArrayList, TestSet) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->set(0, 234);
    a->set(1, 567);
    
    int v;
    to<int>(a->get(0), &v);
    ASSERT_EQ(v, 234);
    to<int>(a->get(1), &v);
    ASSERT_EQ(v, 567);
    ASSERT_EQ(a->size(), 2);
}

TEST(GTestArrayList, TestRemove) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->remove(0);
    
    int v;
    to<int>(a->get(0), &v);
    ASSERT_EQ(v, 456);
    ASSERT_EQ(a->size(), 1);
}

TEST(GTestArrayList, TestRemove2) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->add(789);
    a->remove(static_cast<Value>(456));
    
    int v;
    to<int>(a->get(1), &v);
    ASSERT_EQ(v, 789);
    ASSERT_EQ(a->size(), 2);
}


TEST(GTestArrayList, TestClear) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->clear();
    
    Type<Error>::Cptr e;
    to<Type<Error>::Cptr>(a->get(0), &e);
    ASSERT_TRUE(e->instanceOf(Type<Error>::id()));
    ASSERT_EQ(a->size(), 0);
}

TEST(GTestArrayList, TestError) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    
    Type<Error>::Cptr e;
    ASSERT_TRUE(to<Type<Error>::Cptr>(a->get(0), &e));
    ASSERT_TRUE(e->instanceOf(Type<Error>::id()));
    ASSERT_EQ(e->code(), Error::INDEX_OUT_OF_BOUNDS);
}

TEST(GTestArrayList, TestIterator) {
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    
    int v;
    Type<Iterator>::Ptr itr = a->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v));
    ASSERT_EQ(v, 123);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v));
    ASSERT_EQ(v, 456);
    ASSERT_FALSE(itr->hasNext());
}

}  // namespace libj
