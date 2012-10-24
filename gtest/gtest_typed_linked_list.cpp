// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/typed_linked_list.h>

namespace libj {

TEST(GTestTypedLinkedList, TestCreate) {
    TypedLinkedList<Int>::Ptr l = TypedLinkedList<Int>::create();
    ASSERT_TRUE(!!l);
}

TEST(GTestTypedLinkedList, TestCreate2) {
    LinkedList::Ptr l = LinkedList::create();
    l->add(5);
    TypedLinkedList<Int>::Ptr tl =
        TypedLinkedList<Int>::create(l);
    ASSERT_TRUE(!!tl);

    l->add(7.7);
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(TypedLinkedList<Int>::create(l));
#else
    tl = TypedLinkedList<Int>::create(l);
    ASSERT_FALSE(!!tl);
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestTypedLinkedList, TestAdd) {
    TypedLinkedList<String::CPtr>::Ptr tl =
         TypedLinkedList<String::CPtr>::create();
    tl->add(String::create("abc"));
    ASSERT_EQ(1, tl->size());
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(tl->add(2));
#else
    tl->add(2);
    ASSERT_EQ(1, tl->size());
#endif
}

TEST(GTestTypedLinkedList, TestSubList) {
    TypedLinkedList<int>::Ptr l = TypedLinkedList<int>::create();
    l->add(3);
    l->add(5);
    l->add(7);

    TypedLinkedList<int>::Ptr sub1 =
        toPtr<TypedLinkedList<int> >(l->subList(1, 2));
    ASSERT_TRUE(sub1->toString()->equals(String::create("[5]")));

    TypedLinkedList<int>::Ptr sub2 =
        toPtr<TypedLinkedList<int> >(l->subList(0, 3));
    ASSERT_TRUE(sub2->toString()->equals(String::create("[3, 5, 7]")));

    TypedLinkedList<int>::Ptr sub3 =
        toPtr<TypedLinkedList<int> >(l->subList(2, 2));
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


TEST(GTestTypedLinkedList, TestGetTyped) {
    TypedLinkedList<int>::Ptr l = TypedLinkedList<int>::create();
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(l->getTyped(1));
#endif  // LIBJ_USE_EXCEPTION

    l->add(5);
    l->add(7);
    ASSERT_EQ(7, l->getTyped(1));
}

TEST(GTestTypedLinkedList, TestAddTyped) {
    TypedLinkedList<Int>::Ptr l = TypedLinkedList<Int>::create();
    l->addTyped(9);
    l->addTyped(0, 11);
    ASSERT_EQ(9, l->getTyped(1));
}

TEST(GTestTypedLinkedList, TestSetTyped) {
    TypedLinkedList<Int>::Ptr l = TypedLinkedList<Int>::create();
    l->addTyped(9);
    l->setTyped(0, 11);
    ASSERT_EQ(11, l->getTyped(0));
}

TEST(GTestTypedLinkedList, TestRemoveTyped) {
    TypedLinkedList<Int>::Ptr l = TypedLinkedList<Int>::create();
    l->addTyped(9);
    ASSERT_EQ(9, l->removeTyped(static_cast<Size>(0)));

    l->addTyped(11);
    ASSERT_FALSE(l->removeTyped(9));
    ASSERT_TRUE(l->removeTyped(11));
}

TEST(GTestTypedLinkedList, TestShiftTypedAndUnshiftTyped) {
    TypedLinkedList<Int>::Ptr l = TypedLinkedList<Int>::create();
    ASSERT_EQ(1, l->unshiftTyped(5));
    ASSERT_EQ(2, l->unshiftTyped(7));
    ASSERT_EQ(7, l->getTyped(0));
    ASSERT_EQ(7, l->shiftTyped());
    ASSERT_EQ(5, l->shiftTyped());
    ASSERT_TRUE(l->isEmpty());
}

TEST(GTestTypedLinkedList, TestPushTypedAndPopTyped) {
    TypedLinkedList<Int>::Ptr l = TypedLinkedList<Int>::create();
    ASSERT_EQ(1, l->pushTyped(5));
    ASSERT_EQ(2, l->pushTyped(7));
    ASSERT_EQ(5, l->getTyped(0));
    ASSERT_EQ(7, l->popTyped());
    ASSERT_EQ(5, l->popTyped());
    ASSERT_TRUE(l->isEmpty());
}

TEST(GTestTypedLinkedList, TestIteratorTyped) {
    TypedLinkedList<int>::Ptr l = TypedLinkedList<int>::create();
    l->add(5);
    l->add(7);
    TypedIterator<int>::Ptr i = l->iteratorTyped();
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(5, i->next());
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(7, i->next());
    ASSERT_FALSE(i->hasNext());
}

TEST(GTestTypedLinkedList, TestReverseIteratorTyped) {
    TypedLinkedList<Int>::Ptr l = TypedLinkedList<Int>::create();
    l->add(5);
    l->add(7);
    TypedIterator<Int>::Ptr i = l->reverseIteratorTyped();
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(7, i->next());
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(5, i->next());
    ASSERT_FALSE(i->hasNext());
}

}  // namespace libj
