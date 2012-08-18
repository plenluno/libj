// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/map.h>
#include <libj/string.h>

namespace libj {

TEST(GTestMap, TestCreate) {
    Map::Ptr m = Map::create();
    ASSERT_TRUE(m);
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
    ASSERT_EQ(1, m->size());
    m->put(String::create("y"), 456);
    ASSERT_EQ(2, m->size());
    m->put(123, String::create("x"));
    ASSERT_EQ(3, m->size());
    m->put(456, String::create("y"));
    ASSERT_EQ(4, m->size());
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
    ASSERT_TRUE(v1->equals(x) || v1->equals(y));
    ASSERT_TRUE(itr->hasNext());
    ASSERT_TRUE(to<String::CPtr>(itr->next(), &v2));
    ASSERT_TRUE(!v1->equals(v2) && (v2->equals(x) || v2->equals(y)));
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
    m->put(x, 123);
    ASSERT_TRUE(m->containsValue(123));
    ASSERT_FALSE(m->containsValue(456));
}

#ifdef LIBJ_USE_SP
TEST(GTestMap, TestUseCount) {
    Map::CPtr p = Map::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
