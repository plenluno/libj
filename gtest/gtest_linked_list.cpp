// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/linked_list.h>
#include <libj/error.h>
#include <libj/string.h>

namespace libj {

TEST(GTestLinkedList, TestCreate) {
    LinkedList::Ptr l = LinkedList::create();
    ASSERT_TRUE(!!l);
}

TEST(GTestLinkedList, TestInstanceOf) {
    LinkedList::Ptr l = LinkedList::create();
    ASSERT_TRUE(l->instanceof(Type<LinkedList>::id()));
    ASSERT_TRUE(l->instanceof(Type<List>::id()));
    ASSERT_TRUE(l->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(l->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(l->instanceof(Type<Object>::id()));
}

TEST(GTestLinkedList, TestSize) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    ASSERT_EQ(1, l->size());
    l->add(456);
    ASSERT_EQ(2, l->size());
}

TEST(GTestLinkedList, TestAddAndGet) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->add(1, 789);

    int v;
    to<int>(l->get(0), &v);
    ASSERT_EQ(123, v);
    to<int>(l->get(1), &v);
    ASSERT_EQ(789, v);
    to<int>(l->get(2), &v);
    ASSERT_EQ(456, v);
}

TEST(GTestLinkedList, TestSet) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->set(0, 234);
    l->set(1, 567);

    int v;
    to<int>(l->get(0), &v);
    ASSERT_EQ(234, v);
    to<int>(l->get(1), &v);
    ASSERT_EQ(567, v);
    ASSERT_EQ(2, l->size());
}

TEST(GTestLinkedList, TestRemove) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);
    l->add(789);
    ASSERT_TRUE(l->remove(2).equals(789));
    ASSERT_TRUE(l->remove(0).equals(123));

    int v;
    to<int>(l->get(0), &v);
    ASSERT_EQ(456, v);
    ASSERT_EQ(1, l->size());
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
    ASSERT_EQ(789, v);
    ASSERT_EQ(2, l->size());
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
    ASSERT_TRUE(e->instanceof(Type<Error>::id()));
#endif  // LIBJ_USE_EXCEPTION
    ASSERT_EQ(0, l->size());
}

TEST(GTestLinkedList, TestError) {
    LinkedList::Ptr l = LinkedList::create();

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(l->get(5));
#else
    Error::CPtr e;
    ASSERT_TRUE(to<Error::CPtr>(l->get(0), &e));
    ASSERT_TRUE(e->instanceof(Type<Error>::id()));
    ASSERT_EQ(Error::INDEX_OUT_OF_BOUNDS, e->code());
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestLinkedList, TestIterator) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);

    Iterator::Ptr itr = l->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(123));
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(456));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestLinkedList, TestReverseIterator) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(456);

    Iterator::Ptr itr = l->reverseIterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(456));
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(itr->next().equals(123));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestLinkedList, TestToString) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(123);
    l->add(false);
    l->add(String::create("foo"));
    String::CPtr s = String::create("[123, false, foo]");
    ASSERT_TRUE(l->toString()->equals(s));
}

TEST(GTestLinkedList, TestSubList) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(3);
    l->add(5);
    l->add(7);

    LinkedList::Ptr sub1 = toPtr<LinkedList>(l->subList(1, 2));
    ASSERT_TRUE(sub1->toString()->equals(String::create("[5]")));

    LinkedList::Ptr sub2 = toPtr<LinkedList>(l->subList(0, 3));
    ASSERT_TRUE(sub2->toString()->equals(String::create("[3, 5, 7]")));

    LinkedList::Ptr sub3 = toPtr<LinkedList>(l->subList(2, 2));
    ASSERT_TRUE(sub3->toString()->equals(String::create("[]")));

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(l->subList(0, 4));
    ASSERT_ANY_THROW(l->subList(2, 1));
#else
    ASSERT_EQ(
        Error::INDEX_OUT_OF_BOUNDS,
        toCPtr<Error>(l->subList(0, 4))->code());
    ASSERT_EQ(
        Error::INDEX_OUT_OF_BOUNDS,
        toCPtr<Error>(l->subList(2, 1))->code());
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestLinkedList, TestIsEmpty) {
    LinkedList::Ptr l = LinkedList::create();
    ASSERT_TRUE(l->isEmpty());
    l->add(5);
    ASSERT_FALSE(l->isEmpty());
}

TEST(GTestLinkedList, TestAddAll) {
    LinkedList::Ptr l1 = LinkedList::create();
    l1->add(3);
    l1->add(5);

    LinkedList::Ptr l2 = LinkedList::create();
    l2->add(5);
    l2->add(7);

    ASSERT_TRUE(l1->addAll(l2));
    ASSERT_EQ(4, l1->size());
    ASSERT_TRUE(l1->get(0).equals(3));
    ASSERT_TRUE(l1->get(1).equals(5));
    ASSERT_TRUE(l1->get(2).equals(5));
    ASSERT_TRUE(l1->get(3).equals(7));

    ASSERT_FALSE(l1->addAll(LinkedList::null()));
    ASSERT_FALSE(l1->addAll(LinkedList::create()));
}

TEST(GTestLinkedList, TestContainsAll) {
    LinkedList::Ptr l1 = LinkedList::create();
    l1->add(3);
    l1->add(5);

    LinkedList::Ptr l2 = LinkedList::create();
    l2->add(5);

    LinkedList::Ptr l3 = LinkedList::create();
    l3->add(5);
    l3->add(7);

    ASSERT_TRUE(l1->containsAll(l2));
    ASSERT_FALSE(l1->containsAll(l3));
    ASSERT_FALSE(l1->containsAll(LinkedList::null()));
    ASSERT_TRUE(l1->containsAll(LinkedList::create()));
}

TEST(GTestLinkedList, TestRemoveAll) {
    LinkedList::Ptr l1 = LinkedList::create();
    l1->add(3);
    l1->add(5);
    l1->add(7);
    l1->add(9);
    l1->add(5);

    LinkedList::Ptr l2 = LinkedList::create();
    l2->add(5);
    l2->add(7);

    ASSERT_TRUE(l1->removeAll(l2));
    ASSERT_EQ(2, l1->size());
    ASSERT_TRUE(l1->get(0).equals(3));
    ASSERT_TRUE(l1->get(1).equals(9));

    ASSERT_FALSE(l1->removeAll(LinkedList::null()));
    ASSERT_FALSE(l1->removeAll(LinkedList::create()));
}

TEST(GTestLinkedList, TestRetainAll) {
    LinkedList::Ptr l1 = LinkedList::create();
    l1->add(3);
    l1->add(5);
    l1->add(7);
    l1->add(9);
    l1->add(5);

    LinkedList::Ptr l2 = LinkedList::create();
    l2->add(5);
    l2->add(7);

    ASSERT_TRUE(l1->retainAll(l2));
    ASSERT_EQ(3, l1->size());
    ASSERT_TRUE(l1->get(0).equals(5));
    ASSERT_TRUE(l1->get(1).equals(7));
    ASSERT_TRUE(l1->get(2).equals(5));

    ASSERT_FALSE(l1->retainAll(LinkedList::null()));

    ASSERT_TRUE(l1->retainAll(LinkedList::create()));
    ASSERT_TRUE(l1->isEmpty());
}

TEST(GTestLinkedList, TestShiftAndUnshift) {
    LinkedList::Ptr a = LinkedList::create();
    ASSERT_EQ(1, a->unshift(5));
    ASSERT_EQ(2, a->unshift(7));
    ASSERT_TRUE(a->get(0).equals(7));
    ASSERT_TRUE(a->shift().equals(7));
    ASSERT_TRUE(a->shift().equals(5));
    ASSERT_TRUE(a->isEmpty());
}

TEST(GTestLinkedList, TestPushAndPop) {
    LinkedList::Ptr a = LinkedList::create();
    ASSERT_EQ(1, a->push(5));
    ASSERT_EQ(2, a->push(7));
    ASSERT_TRUE(a->get(0).equals(5));
    ASSERT_TRUE(a->pop().equals(7));
    ASSERT_TRUE(a->pop().equals(5));
    ASSERT_TRUE(a->isEmpty());
}

TEST(GTestLinkedList, TestIndexOfAndLastIndexOf) {
    LinkedList::Ptr a = LinkedList::create();
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
TEST(GTestLinkedList, TestUseCount) {
    LinkedList::CPtr p = LinkedList::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
