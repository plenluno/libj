// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/map.h>

namespace libj {

TEST(GTestMap, TestCreate) {
    Type<Map>::Ptr m = Map::create();
    ASSERT_EQ(m->size(), 0);
}

TEST(GTestMap, TestInstanceOf) {
    Type<Map>::Ptr m = Map::create();
    ASSERT_TRUE(m->instanceOf(Type<Map>::id()));
    ASSERT_TRUE(m->instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(m->instanceOf(Type<Object>::id()));
}

TEST(GTestMap, TestSize) {
    Type<Map>::Ptr m = Map::create();
    m->put(String::create("x"), 123);
    ASSERT_EQ(m->size(), 1);
    m->put(String::create("y"), 456);
    ASSERT_EQ(m->size(), 2);
    m->put(123, String::create("x"));
    ASSERT_EQ(m->size(), 3);
    m->put(456, String::create("y"));
    ASSERT_EQ(m->size(), 4);
}

TEST(GTestMap, TestIterator) {
    Type<Map>::Ptr m = Map::create();
    Type<String>::Cptr x = String::create("x");
    Type<String>::Cptr y = String::create("y");
    m->put(x, 123);
    m->put(y, 456);
    
    Type<String>::Cptr v1, v2;
    Type<Set>::Cptr ks = m->keySet();
    Type<Iterator>::Ptr itr = ks->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<Type<String>::Cptr>(itr->next(), &v1));
    ASSERT_TRUE(v1->compareTo(x) == 0 || v1->compareTo(y) == 0);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<Type<String>::Cptr>(itr->next(), &v2));
    ASSERT_TRUE(v1->compareTo(v2) != 0 &&
        (v2->compareTo(x) == 0 || v2->compareTo(y) == 0));
    ASSERT_FALSE(itr->hasNext());
}

}  // namespace libj
