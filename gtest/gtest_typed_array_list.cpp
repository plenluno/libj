// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/typed_array_list.h>

namespace libj {

TEST(GTestTypedArrayList, TestCreate) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_EQ(a->size(), 0);
}

TEST(GTestTypedArrayList, TestGetTyped) {
    TypedArrayList<Int>::Ptr a = TypedArrayList<Int>::create();
    ASSERT_ANY_THROW(a->getTyped(1));
}

}  // namespace libj
