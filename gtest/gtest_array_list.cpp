// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/array_list.h>
#include <libj/error.h>
#include <libj/string.h>

namespace libj {

TEST(GTestArrayList, TestCreate) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_TRUE(!!a);
}

TEST(GTestArrayList, TestInstanceOf) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_TRUE(a->instanceof(Type<ArrayList>::id()));
    ASSERT_TRUE(a->instanceof(Type<List>::id()));
    ASSERT_TRUE(a->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(a->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceof(Type<Object>::id()));
}

TEST(GTestArrayList, TestInstanceOf2) {
    ArrayList::CPtr a = ArrayList::create();
    ASSERT_TRUE(a->instanceof(Type<ArrayList>::id()));
    ASSERT_TRUE(a->instanceof(Type<List>::id()));
    ASSERT_TRUE(a->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(a->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceof(Type<Object>::id()));
}

TEST(GTestArrayList, TestSize) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_EQ(0, a->size());
    a->add(123);
    ASSERT_EQ(1, a->size());
    a->add(String::create("abc"));
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
    ASSERT_EQ(3, a->size());
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
        String::CPtr s;
        s = String::create("a");
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

TEST(GTestArrayList, TestRemove4) {
    ArrayList::Ptr a = ArrayList::create();
    {
        String::CPtr s;
        s = String::create("a");
        a->add(s);
        s = String::create("b");
        a->add(s);
    }

    a->remove(String::create("a"));
    ASSERT_TRUE(a->get(0).equals(String::create("b")));
    ASSERT_EQ(1, a->size());
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
    ASSERT_TRUE(to<Error::CPtr>(a->get(5), &e));
    ASSERT_TRUE(e->instanceof(Type<Error>::id()));
    ASSERT_EQ(Error::INDEX_OUT_OF_BOUNDS, e->code());
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestArrayList, TestIterator) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);

    Iterator::Ptr itr = a->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(123));
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(456));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestArrayList, TestReverseIterator) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(123);
    a->add(456);

    Iterator::Ptr itr = a->reverseIterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(456));
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(123));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestArrayList, TestToString) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(1);
    ArrayList::Ptr a2 = ArrayList::create();
    a2->add(3);
    a2->add(5);
    a->add(a2);
    a->add(Object::null());
    a->add(UNDEFINED);
    ASSERT_TRUE(a->toString()->equals(
        String::create("[1, [3, 5], null, undefined]")));
}

TEST(GTestArrayList, TestSubList) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(3);
    a->add(5);
    a->add(7);

    ArrayList::Ptr sub1 = toPtr<ArrayList>(a->subList(1, 2));
    ASSERT_TRUE(sub1->toString()->equals(String::create("[5]")));

    ArrayList::Ptr sub2 = toPtr<ArrayList>(a->subList(0, 3));
    ASSERT_TRUE(sub2->toString()->equals(String::create("[3, 5, 7]")));

    ArrayList::Ptr sub3 = toPtr<ArrayList>(a->subList(2, 2));
    ASSERT_TRUE(sub3->toString()->equals(String::create("[]")));

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(a->subList(0, 4));
    ASSERT_ANY_THROW(a->subList(2, 1));
#else
    ASSERT_EQ(
        Error::INDEX_OUT_OF_BOUNDS,
        toCPtr<Error>(a->subList(0, 4))->code());
    ASSERT_EQ(
        Error::INDEX_OUT_OF_BOUNDS,
        toCPtr<Error>(a->subList(2, 1))->code());
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestArrayList, TestIsEmpty) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_TRUE(a->isEmpty());
    a->add(5);
    ASSERT_FALSE(a->isEmpty());
}

TEST(GTestArrayList, TestAddAll) {
    ArrayList::Ptr a1 = ArrayList::create();
    a1->add(3);
    a1->add(5);

    ArrayList::Ptr a2 = ArrayList::create();
    a2->add(5);
    a2->add(7);

    ASSERT_TRUE(a1->addAll(a2));
    ASSERT_EQ(4, a1->size());
    ASSERT_TRUE(a1->get(0).equals(3));
    ASSERT_TRUE(a1->get(1).equals(5));
    ASSERT_TRUE(a1->get(2).equals(5));
    ASSERT_TRUE(a1->get(3).equals(7));

    ASSERT_FALSE(a1->addAll(ArrayList::null()));
    ASSERT_FALSE(a1->addAll(ArrayList::create()));
}

TEST(GTestArrayList, TestContainsAll) {
    ArrayList::Ptr a1 = ArrayList::create();
    a1->add(3);
    a1->add(5);

    ArrayList::Ptr a2 = ArrayList::create();
    a2->add(5);

    ArrayList::Ptr a3 = ArrayList::create();
    a3->add(5);
    a3->add(7);

    ASSERT_TRUE(a1->containsAll(a2));
    ASSERT_FALSE(a1->containsAll(a3));
    ASSERT_FALSE(a1->containsAll(ArrayList::null()));
    ASSERT_TRUE(a1->containsAll(ArrayList::create()));
}

TEST(GTestArrayList, TestRemoveAll) {
    ArrayList::Ptr a1 = ArrayList::create();
    a1->add(3);
    a1->add(5);
    a1->add(7);
    a1->add(9);
    a1->add(5);

    ArrayList::Ptr a2 = ArrayList::create();
    a2->add(5);
    a2->add(7);

    ASSERT_TRUE(a1->removeAll(a2));
    ASSERT_EQ(2, a1->size());
    ASSERT_TRUE(a1->get(0).equals(3));
    ASSERT_TRUE(a1->get(1).equals(9));

    ASSERT_FALSE(a1->removeAll(ArrayList::null()));
    ASSERT_FALSE(a1->removeAll(ArrayList::create()));
}

TEST(GTestArrayList, TestRetainAll) {
    ArrayList::Ptr a1 = ArrayList::create();
    a1->add(3);
    a1->add(5);
    a1->add(7);
    a1->add(9);
    a1->add(5);

    ArrayList::Ptr a2 = ArrayList::create();
    a2->add(5);
    a2->add(7);

    ASSERT_TRUE(a1->retainAll(a2));
    ASSERT_EQ(3, a1->size());
    ASSERT_TRUE(a1->get(0).equals(5));
    ASSERT_TRUE(a1->get(1).equals(7));
    ASSERT_TRUE(a1->get(2).equals(5));

    ASSERT_FALSE(a1->retainAll(ArrayList::null()));

    ASSERT_TRUE(a1->retainAll(ArrayList::create()));
    ASSERT_TRUE(a1->isEmpty());
}

TEST(GTestArrayList, TestShiftAndUnshift) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_EQ(1, a->unshift(5));
    ASSERT_EQ(2, a->unshift(7));
    ASSERT_TRUE(a->get(0).equals(7));
    ASSERT_TRUE(a->shift().equals(7));
    ASSERT_TRUE(a->shift().equals(5));
    ASSERT_TRUE(a->isEmpty());
}

TEST(GTestArrayList, TestPushAndPop) {
    ArrayList::Ptr a = ArrayList::create();
    ASSERT_EQ(1, a->push(5));
    ASSERT_EQ(2, a->push(7));
    ASSERT_TRUE(a->get(0).equals(5));
    ASSERT_TRUE(a->pop().equals(7));
    ASSERT_TRUE(a->pop().equals(5));
    ASSERT_TRUE(a->isEmpty());
}

TEST(GTestArrayList, TestIndexOfAndLastIndexOf) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(3);
    a->add(5);
    a->add(7);
    a->add(9);
    a->add(5);

    ASSERT_EQ(1, a->indexOf(5));
    ASSERT_EQ(3, a->indexOf(9));
    ASSERT_EQ(-1, a->indexOf(11));

    ASSERT_EQ(4, a->lastIndexOf(5));
    ASSERT_EQ(3, a->lastIndexOf(9));
    ASSERT_EQ(-1, a->lastIndexOf(11));
}

#ifdef LIBJ_USE_SP
TEST(GTestArrayList, TestUseCount) {
    ArrayList::CPtr p = ArrayList::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
