// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/typed_array_list.h>

namespace libj {

TEST(GTestTypedArrayList, TestCreate) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_TRUE(a);
}

TEST(GTestTypedArrayList, TestCreate2) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(5);
    TypedArrayList<int>::Ptr ta =
        TypedArrayList<int>::create(a);
    ASSERT_TRUE(ta);
    a->add(7.7);
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(TypedArrayList<int>::create(a));
#else
    ta = TypedArrayList<int>::create(a);
    ASSERT_FALSE(ta);
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

#ifdef LIBJ_USE_EXCEPTION
TEST(GTestTypedArrayList, TestGetTyped) {
    TypedArrayList<int>::Ptr a = TypedArrayList<int>::create();
    ASSERT_ANY_THROW(a->getTyped(1));
    a->add(5);
    a->add(7);
    ASSERT_EQ(7, a->getTyped(1));
}

TEST(GTestTypedArrayList, TestIteratorTyped) {
    TypedArrayList<int>::Ptr a = TypedArrayList<int>::create();
    a->add(5);
    a->add(7);
    TypedIterator<int>::Ptr i = a->iteratorTyped();
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(5, i->nextTyped());
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(7, i->nextTyped());
    ASSERT_FALSE(i->hasNext());
}
#endif  // LIBJ_USE_EXCEPTION

}  // namespace libj
