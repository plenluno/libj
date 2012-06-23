// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/map.h>
#include <libj/string.h>

namespace libj {

TEST(GTestMap, TestCreate) {
    Map::Ptr m = Map::create();
    ASSERT_EQ(m->size(), 0);
}

TEST(GTestMap, TestInstanceOf) {
    Map::Ptr m = Map::create();
    ASSERT_TRUE(m->instanceof(Type<Map>::id()));
    ASSERT_TRUE(m->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(m->instanceof(Type<Object>::id()));
}

TEST(GTestMap, TestSize) {
    Map::Ptr m = Map::create();
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
    Map::Ptr m = Map::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    m->put(x, 123);
    m->put(y, 456);

    String::CPtr v1, v2;
    Set::CPtr ks = m->keySet();
    Iterator::Ptr itr = ks->iterator();
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<String::CPtr>(itr->next(), &v1));
    ASSERT_TRUE(v1->compareTo(x) == 0 || v1->compareTo(y) == 0);
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<String::CPtr>(itr->next(), &v2));
    ASSERT_TRUE(v1->compareTo(v2) != 0 &&
        (v2->compareTo(x) == 0 || v2->compareTo(y) == 0));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestMap, TestContainsKey) {
    Map::Ptr m = Map::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    m->put(x, 123);
    ASSERT_TRUE(m->containsKey(x));
    ASSERT_FALSE(m->containsKey(y));
}

TEST(GTestMap, TestContainsValue) {
    Map::Ptr m = Map::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    m->put(x, 123);
    ASSERT_TRUE(m->containsValue(123));
    ASSERT_FALSE(m->containsKey(456));
}

#ifdef LIBJ_USE_SP
TEST(GTestMap, TestUseCount) {
    Map::CPtr p = Map::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
