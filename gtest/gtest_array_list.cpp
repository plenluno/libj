// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/array_list.h>
#include <libj/error.h>
#include <libj/string.h>

namespace libj {

TEST(GTestArrayList, TestCreate) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_TRUE(a);
}

TEST(GTestArrayList, TestInstanceOf) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_TRUE(a->instanceof(Type<ArrayList>::id()));
    ASSERT_TRUE(a->instanceof(Type<List>::id()));
    ASSERT_TRUE(a->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(a->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceof(Type<Object>::id()));
}

TEST(GTestArrayList, TestSize) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    ASSERT_EQ(1, a->size());
    a->add(456);
    ASSERT_EQ(2, a->size());
}

TEST(GTestArrayList, TestAddAndGet) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->add(1, 789);

    int v;
    to<int>(a->get(0), &v);
    ASSERT_EQ(123, v);
    to<int>(a->get(1), &v);
    ASSERT_EQ(789, v);
    to<int>(a->get(2), &v);
    ASSERT_EQ(456, v);
}

TEST(GTestArrayList, TestSet) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->set(0, 234);
    a->set(1, 567);

    int v;
    to<int>(a->get(0), &v);
    ASSERT_EQ(234, v);
    to<int>(a->get(1), &v);
    ASSERT_EQ(567, v);
    ASSERT_EQ(2, a->size());
}

TEST(GTestArrayList, TestRemove) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);
    a->remove(0);

    int v;
    to<int>(a->get(0), &v);
    ASSERT_EQ(456, v);
    ASSERT_EQ(1, a->size());
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
    ASSERT_EQ(789, v);
    ASSERT_EQ(2, a->size());
}

TEST(GTestArrayList, TestRemove3) {
    ArrayList::Ptr a = ArrayList::create();
    {
        String::CPtr s = String::create("a");
        a->add(s);
        s = String::create("b");
        a->add(s);
    }

    a->remove(0);
    ASSERT_TRUE(a->get(0).equals(String::create("b")));
    ASSERT_EQ(1, a->size());

    a->remove(0);
    ASSERT_EQ(0, a->size());
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
    ASSERT_TRUE(e->instanceof(Type<Error>::id()));
#endif  // LIBJ_USE_EXCEPTION
    ASSERT_EQ(0, a->size());
}

TEST(GTestArrayList, TestError) {
    ArrayList::Ptr a = ArrayList::create();

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(a->get(5));
#else
    Error::CPtr e;
    ASSERT_TRUE(to<Error::CPtr>(a->get(0), &e));
    ASSERT_TRUE(e->instanceof(Type<Error>::id()));
    ASSERT_EQ(Error::INDEX_OUT_OF_BOUNDS, e->code());
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
    ASSERT_EQ(123, v);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v));
    ASSERT_EQ(456, v);
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestArrayList, TestToString) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(1);
    ArrayList::Ptr a2 = ArrayList::create();
    a2->add(3);
    a2->add(5);
    a->add(a2);
    a->add(7);
    ASSERT_TRUE(a->toString()->equals(String::create("1,3,5,7")));
}

#ifdef LIBJ_USE_SP
TEST(GTestArrayList, TestUseCount) {
    ArrayList::CPtr p = ArrayList::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
