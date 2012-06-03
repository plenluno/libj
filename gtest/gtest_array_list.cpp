// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/array_list.h>
#include <libj/error.h>

namespace libj {

TEST(GTestArrayList, TestCreate) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_EQ(a->size(), 0);
}

TEST(GTestArrayList, TestInstanceOf) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_TRUE(a->instanceOf(Type<ArrayList>::id()));
    ASSERT_TRUE(a->instanceOf(Type<List>::id()));
    ASSERT_TRUE(a->instanceOf(Type<Collection>::id()));
    ASSERT_TRUE(a->instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceOf(Type<Object>::id()));
}

TEST(GTestArrayList, TestSize) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    ASSERT_EQ(a->size(), 1);
    a->add(456);
    ASSERT_EQ(a->size(), 2);
}

TEST(GTestArrayList, TestAddAndGet) {
    ArrayList::Ptr a = ArrayList::create();
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
    ArrayList::Ptr a = ArrayList::create();
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
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->remove(0);

    int v;
    to<int>(a->get(0), &v);
    ASSERT_EQ(v, 456);
    ASSERT_EQ(a->size(), 1);
}

TEST(GTestArrayList, TestRemove2) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->add(789);
    ASSERT_TRUE(a->remove(static_cast<Value>(456)));
    ASSERT_FALSE(a->remove(static_cast<Value>(567)));

    int v;
    to<int>(a->get(1), &v);
    ASSERT_EQ(v, 789);
    ASSERT_EQ(a->size(), 2);
}


TEST(GTestArrayList, TestClear) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->clear();

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(a->get(0));
#else
    Error::CPtr e;
    ASSERT_TRUE(to<Error::CPtr>(a->get(0), &e));
    ASSERT_TRUE(e->instanceOf(Type<Error>::id()));
#endif  // LIBJ_USE_EXCEPTION
    ASSERT_EQ(a->size(), 0);
}

TEST(GTestArrayList, TestError) {
    ArrayList::Ptr a = ArrayList::create();

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(a->get(5));
#else
    Error::CPtr e;
    ASSERT_TRUE(to<Error::CPtr>(a->get(0), &e));
    ASSERT_TRUE(e->instanceOf(Type<Error>::id()));
    ASSERT_EQ(e->code(), Error::INDEX_OUT_OF_BOUNDS);
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestArrayList, TestIterator) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);

    int v;
    Iterator::Ptr itr = a->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v));
    ASSERT_EQ(v, 123);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v));
    ASSERT_EQ(v, 456);
    ASSERT_FALSE(itr->hasNext());
}

#ifdef LIBJ_USE_SP
TEST(GTestArrayList, TestUseCount) {
    ArrayList::CPtr p = ArrayList::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
