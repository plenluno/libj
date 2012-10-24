// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/typed_array_list.h>

namespace libj {

TEST(GTestTypedArrayList, TestCreate) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_TRUE(!!a);
}

TEST(GTestTypedArrayList, TestCreate2) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(5);
    TypedArrayList<Int>::Ptr ta =
        TypedArrayList<Int>::create(a);
    ASSERT_TRUE(!!ta);

    a->add(7.7);
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(TypedArrayList<Int>::create(a));
#else
    ta = TypedArrayList<Int>::create(a);
    ASSERT_FALSE(!!ta);
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestTypedArrayList, TestAdd) {
    TypedArrayList<String::CPtr>::Ptr ta =
         TypedArrayList<String::CPtr>::create();
    ta->add(String::create("abc"));
    ASSERT_EQ(1, ta->size());
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(ta->add(2));
#else
    ta->add(2);
    ASSERT_EQ(1, ta->size());
#endif
}

TEST(GTestTypedArrayList, TestSubList) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    a->add(3);
    a->add(5);
    a->add(7);

    TypedArrayList<Int>::Ptr sub1 =
        toPtr<TypedArrayList<Int> >(a->subList(1, 2));
    ASSERT_TRUE(sub1->toString()->equals(String::create("[5]")));

    TypedArrayList<Int>::Ptr sub2 =
        toPtr<TypedArrayList<Int> >(a->subList(0, 3));
    ASSERT_TRUE(sub2->toString()->equals(String::create("[3, 5, 7]")));

    TypedArrayList<Int>::Ptr sub3 =
        toPtr<TypedArrayList<Int> >(a->subList(2, 2));
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

TEST(GTestTypedArrayList, TestGetTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(a->getTyped(1));
#endif

    a->add(5);
    a->add(7);
    ASSERT_EQ(7, a->getTyped(1));
}

TEST(GTestTypedArrayList, TestAddTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    a->addTyped(9);
    a->addTyped(0, 11);
    ASSERT_EQ(9, a->getTyped(1));
}

TEST(GTestTypedArrayList, TestSetTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    a->addTyped(9);
    a->setTyped(0, 11);
    ASSERT_EQ(11, a->getTyped(0));
}

TEST(GTestTypedArrayList, TestRemoveTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    a->addTyped(9);
    ASSERT_EQ(9, a->removeTyped(static_cast<Size>(0)));

    a->addTyped(11);
    ASSERT_FALSE(a->removeTyped(9));
    ASSERT_TRUE(a->removeTyped(11));
}

TEST(GTestTypedArrayList, TestShiftTypedAndUnshiftTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_EQ(1, a->unshiftTyped(5));
    ASSERT_EQ(2, a->unshiftTyped(7));
    ASSERT_EQ(7, a->getTyped(0));
    ASSERT_EQ(7, a->shiftTyped());
    ASSERT_EQ(5, a->shiftTyped());
    ASSERT_TRUE(a->isEmpty());
}

TEST(GTestTypedArrayList, TestPushTypedAndPopTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_EQ(1, a->pushTyped(5));
    ASSERT_EQ(2, a->pushTyped(7));
    ASSERT_EQ(5, a->getTyped(0));
    ASSERT_EQ(7, a->popTyped());
    ASSERT_EQ(5, a->popTyped());
    ASSERT_TRUE(a->isEmpty());
}

TEST(GTestTypedArrayList, TestIteratorTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    a->add(5);
    a->add(7);
    TypedIterator<Int>::Ptr i = a->iteratorTyped();
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(5, i->next());
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(7, i->next());
    ASSERT_FALSE(i->hasNext());
}

TEST(GTestTypedArrayList, TestReverseIteratorTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    a->add(5);
    a->add(7);
    TypedIterator<Int>::Ptr i = a->reverseIteratorTyped();
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(7, i->next());
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(5, i->next());
    ASSERT_FALSE(i->hasNext());
}

}  // namespace libj
