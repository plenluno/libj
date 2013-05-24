// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/typed_set.h>

namespace libj {

TEST(GTestTypedSet, TestCreate) {
    TypedSet<Int>::Ptr s = TypedSet<Int>::create();
    ASSERT_TRUE(!!s);
}

TEST(GTestTypedSet, TestInstanceOf) {
    TypedSet<Int>::Ptr s = TypedSet<Int>::create();
    ASSERT_TRUE(s->instanceof(Type<TypedSet<Int> >::id()));
    ASSERT_TRUE(s->instanceof(Type<Set>::id()));
    ASSERT_TRUE(s->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(s->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(s->instanceof(Type<Object>::id()));
}

TEST(GTestTypedSet, TestAddTyped) {
    TypedSet<Int>::Ptr s = TypedSet<Int>::create();
    s->addTyped(9);
    s->addTyped(11);
    ASSERT_TRUE(s->contains(9));
    ASSERT_TRUE(s->contains(11));
    ASSERT_FALSE(s->contains(13));
}

TEST(GTestTypedSet, TestRemoveTyped) {
    TypedSet<Int>::Ptr s = TypedSet<Int>::create();
    s->addTyped(9);
    ASSERT_TRUE(s->removeTyped(9));

    s->addTyped(11);
    ASSERT_FALSE(s->removeTyped(9));
    ASSERT_TRUE(s->removeTyped(11));
    ASSERT_TRUE(s->isEmpty());
}

TEST(GTestTypedSet, TestIteratorTyped) {
    TypedSet<Int>::Ptr s = TypedSet<Int>::create();
    s->add(5);
    s->add(7);
    TypedIterator<Int>::Ptr i = s->iteratorTyped();
    Int x, y;
    ASSERT_TRUE(i->hasNext());
    x = i->next();
    ASSERT_TRUE(x == 5 || x == 7);
    ASSERT_TRUE(i->hasNext());
    y = i->next();
    ASSERT_TRUE(y == 5 || y == 7);
    ASSERT_NE(x, y);
    ASSERT_FALSE(i->hasNext());
}

}  // namespace libj
