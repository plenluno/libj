// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/array_list.h>
#include <libj/typed_value_holder.h>

namespace libj {

TEST(GTestTypedValueHolder, TestCreate) {
    TypedValueHolder<Int>::Ptr h = TypedValueHolder<Int>::create(1);
    ASSERT_TRUE(!!h);

    TypedValueHolder<String::CPtr>::Ptr h2 =
        TypedValueHolder<String::CPtr>::create(String::create("123"));
    ASSERT_TRUE(!!h2);
}

TEST(GTestTypedValueHolder, TestGet) {
    TypedValueHolder<Int>::Ptr h = TypedValueHolder<Int>::create(3);
    ASSERT_EQ(3, h->getTyped());
}

TEST(GTestTypedValueHolder, TestGetPtr) {
    ArrayList::Ptr a = ArrayList::create();
    TypedValueHolder<ArrayList::Ptr>::Ptr h =
        TypedValueHolder<ArrayList::Ptr>::create(a);
    ASSERT_TRUE(h->getTyped()->equals(a));

    ASSERT_TRUE(a->isEmpty());
    h->getTyped()->add(5);
    ASSERT_TRUE(a->get(0).equals(5));
}

TEST(GTestTypedValueHolder, TestGetCPtr) {
    String::CPtr s = String::create("abc");
    TypedValueHolder<String::CPtr>::Ptr h =
        TypedValueHolder<String::CPtr>::create(s);
    ASSERT_TRUE(h->getTyped()->equals(s));
}

TEST(GTestTypedValueHolder, TestSet) {
    String::CPtr s = String::create("abc");
    TypedValueHolder<String::CPtr>::Ptr h =
        TypedValueHolder<String::CPtr>::create(s);

    h->setTyped(h->getTyped()->concat(String::create("123")));
    ASSERT_TRUE(h->getTyped()->equals(String::create("abc123")));
}

class GTestTypedValueHolderIncrement {
 public:
    TypedValueHolder<Int>::Ptr holder;

    void inc() {
        holder->setTyped(holder->getTyped() + 1);
    }
};

TEST(GTestTypedValueHolder, TestSet2) {
    GTestTypedValueHolderIncrement i1;
    GTestTypedValueHolderIncrement i2;
    TypedValueHolder<Int>::Ptr h = TypedValueHolder<Int>::create(0);
    i1.holder = h;
    i2.holder = h;
    i1.inc();
    i2.inc();
    ASSERT_EQ(2, h->getTyped());
}

}  // namespace libj
