// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/array_list.h>
#include <libj/value_holder.h>

namespace libj {

TEST(GTestValueHolder, TestCreate) {
    ValueHolder::Ptr h = ValueHolder::create(1);
    ASSERT_TRUE(!!h);
}

TEST(GTestValueHolder, TestGet) {
    ValueHolder::Ptr h = ValueHolder::create(3);
    ASSERT_TRUE(h->get().equals(3));
}

TEST(GTestValueHolder, TestGetPtr) {
    ArrayList::Ptr a = ArrayList::create();
    ValueHolder::Ptr h = ValueHolder::create(a);
    ASSERT_TRUE(h->get().equals(a));
    ASSERT_TRUE(h->getPtr<ArrayList>()->equals(a));

    ASSERT_TRUE(a->isEmpty());
    h->getPtr<ArrayList>()->add(5);
    ASSERT_TRUE(a->get(0).equals(5));
}

TEST(GTestValueHolder, TestGetCPtr) {
    String::CPtr s = String::create("abc");
    ValueHolder::Ptr h = ValueHolder::create(s);
    ASSERT_TRUE(h->get().equals(s));
    ASSERT_TRUE(h->getCPtr<String>()->equals(s));
}

TEST(GTestValueHolder, TestSet) {
    String::CPtr s = String::create("abc");
    ValueHolder::Ptr h = ValueHolder::create(s);

    h->set(h->getCPtr<String>()->concat(String::create("123")));
    ASSERT_TRUE(h->get().equals(String::create("abc123")));
}

class GTestValueHolderIncrement {
 public:
    ValueHolder::Ptr holder;

    void inc() {
        Value v = holder->get();
        Int i;
        to<Int>(v, &i);
        holder->set(++i);
    }
};

TEST(GTestValueHolder, TestSet2) {
    GTestValueHolderIncrement i1;
    GTestValueHolderIncrement i2;
    ValueHolder::Ptr h = ValueHolder::create(0);
    i1.holder = h;
    i2.holder = h;
    i1.inc();
    i2.inc();
    ASSERT_TRUE(h->get().equals(2));
}

}  // namespace libj
