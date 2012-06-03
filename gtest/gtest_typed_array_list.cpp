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
    TypedArrayList<int>::Ptr ta = TypedArrayList<int>::create(a);
    ASSERT_TRUE(ta);
    a->add(7.7);
    ta = TypedArrayList<int>::create(a);
    ASSERT_FALSE(ta);
}

#ifdef LIBJ_USE_EXCEPTION
TEST(GTestTypedArrayList, TestGetTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_ANY_THROW(a->getTyped(1));
}
#endif  // LIBJ_USE_EXCEPTION

}  // namespace libj
