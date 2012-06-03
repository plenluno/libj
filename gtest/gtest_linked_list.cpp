// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/linked_list.h>
#include <libj/error.h>
#include <libj/string.h>

namespace libj {

TEST(GTestLinkedList, TestCreate) {
    LinkedList::Ptr l = LinkedList::create();
    ASSERT_EQ(l->size(), 0);
}

TEST(GTestLinkedList, TestInstanceOf) {
    LinkedList::Ptr l = LinkedList::create();
    ASSERT_TRUE(l->instanceOf(Type<LinkedList>::id()));
    ASSERT_TRUE(l->instanceOf(Type<List>::id()));
    ASSERT_TRUE(l->instanceOf(Type<Collection>::id()));
    ASSERT_TRUE(l->instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(l->instanceOf(Type<Object>::id()));
}

TEST(GTestLinkedList, TestSize) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    ASSERT_EQ(l->size(), 1);
    l->add(456);
    ASSERT_EQ(l->size(), 2);
}

TEST(GTestLinkedList, TestAddAndGet) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->add(1, 789);

    int v;
    to<int>(l->get(0), &v);
    ASSERT_EQ(v, 123);
    to<int>(l->get(1), &v);
    ASSERT_EQ(v, 789);
    to<int>(l->get(2), &v);
    ASSERT_EQ(v, 456);
}

TEST(GTestLinkedList, TestSet) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->set(0, 234);
    l->set(1, 567);

    int v;
    to<int>(l->get(0), &v);
    ASSERT_EQ(v, 234);
    to<int>(l->get(1), &v);
    ASSERT_EQ(v, 567);
    ASSERT_EQ(l->size(), 2);
}

TEST(GTestLinkedList, TestRemove) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->remove(0);

    int v;
    to<int>(l->get(0), &v);
    ASSERT_EQ(v, 456);
    ASSERT_EQ(l->size(), 1);
}

TEST(GTestLinkedList, TestRemove2) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->add(789);
    ASSERT_TRUE(l->remove(static_cast<Value>(456)));
    ASSERT_FALSE(l->remove(static_cast<Value>(567)));

    int v;
    to<int>(l->get(1), &v);
    ASSERT_EQ(v, 789);
    ASSERT_EQ(l->size(), 2);
}


TEST(GTestLinkedList, TestClear) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->clear();

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(l->get(0));
#else
    Error::CPtr e;
    ASSERT_TRUE(to<Error::CPtr>(l->get(0), &e));
    ASSERT_TRUE(e->instanceOf(Type<Error>::id()));
#endif  // LIBJ_USE_EXCEPTION
    ASSERT_EQ(l->size(), 0);
}

TEST(GTestLinkedList, TestError) {
    LinkedList::Ptr l = LinkedList::create();

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(l->get(5));
#else
    Error::CPtr e;
    ASSERT_TRUE(to<Error::CPtr>(l->get(0), &e));
    ASSERT_TRUE(e->instanceOf(Type<Error>::id()));
    ASSERT_EQ(e->code(), Error::INDEX_OUT_OF_BOUNDS);
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestLinkedList, TestIterator) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);

    int v;
    Iterator::Ptr itr = l->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v));
    ASSERT_EQ(v, 123);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<int>(itr->next(), &v));
    ASSERT_EQ(v, 456);
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestLinkedList, TestToString) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(false);
    l->add(String::create("foo"));
    String::CPtr s = String::create("123,false,foo");
    ASSERT_EQ(l->toString()->compareTo(s), 0);
}

#ifdef LIBJ_USE_SP
TEST(GTestLinkedList, TestUseCount) {
    LinkedList::CPtr p = LinkedList::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
