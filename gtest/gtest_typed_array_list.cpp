// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_typed_array.h>
#include <libj/typed_array_list.h>

namespace libj {

TEST(GTestTypedArrayList, TestCreate) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_TRUE(a);
}

TEST(GTestTypedArrayList, TestCreate2) {
    ArrayList::Ptr a = ArrayList::create();
    a->add(5);
    TypedArrayList<int>::Ptr ta = TypedArrayList<int>::create(a);
    ASSERT_TRUE(ta);
    a->add(7.7);
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(TypedArrayList<int>::create(a));
#else
    ta = TypedArrayList<int>::create(a);
    ASSERT_FALSE(ta);
#endif  // LIBJ_USE_EXCEPTION
}

#ifdef LIBJ_USE_EXCEPTION
TEST(GTestTypedArrayList, TestGetTyped) {
    TypedArrayList<int>::Ptr a = TypedArrayList<int>::create();
    ASSERT_ANY_THROW(a->getTyped(1));
    a->add(5);
    a->add(7);
    ASSERT_EQ(a->getTyped(1), 7);
}

TEST(GTestTypedArrayList, TestIteratorTyped) {
    TypedArrayList<int>::Ptr a = TypedArrayList<int>::create();
    a->add(5);
    a->add(7);
    TypedIterator<int>::Ptr i = a->iteratorTyped();
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(i->nextTyped(), 5);
    ASSERT_TRUE(i->hasNext());
    ASSERT_EQ(i->nextTyped(), 7);
    ASSERT_FALSE(i->hasNext());
}
#endif  // LIBJ_USE_EXCEPTION

TEST(GTestTypedArrayList, TestJsTypedArray) {
    JsInt32Array::Ptr a = JsInt32Array::create();
    a->add(5);
    a->add(7);
    Value v = a->get(1);
    Int i;
    to<Int>(v, &i);
    ASSERT_EQ(i, 7);
}

}  // namespace libj
