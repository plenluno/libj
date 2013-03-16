// Copyright (c) 2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/concurrent_map.h>

namespace libj {

TEST(GTestConcurrentMap, TestCreate) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    ASSERT_TRUE(!!m);
}

TEST(GTestConcurrentMap, TestInstanceOf) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    ASSERT_TRUE(m->instanceof(Type<Map>::id()));
    ASSERT_TRUE(m->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(m->instanceof(Type<Object>::id()));
}

TEST(GTestConcurrentMap, TestInstanceOf2) {
    ConcurrentMap::CPtr m = ConcurrentMap::create();
    ASSERT_TRUE(m->instanceof(Type<Map>::id()));
    ASSERT_TRUE(m->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(m->instanceof(Type<Object>::id()));
}

TEST(GTestConcurrentMap, TestSize) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    m->put(String::create("x"), 123);
    ASSERT_EQ(1, m->size());
    m->put(String::create("y"), 456);
    ASSERT_EQ(2, m->size());
    m->put(123, String::create("x"));
    ASSERT_EQ(3, m->size());
    m->put(456, String::create("y"));
    ASSERT_EQ(4, m->size());
    m->put(Object::null(), String::null());
    ASSERT_EQ(5, m->size());
    m->put(UNDEFINED, UNDEFINED);
    ASSERT_EQ(6, m->size());
}

TEST(GTestConcurrentMap, TestPutAndGet) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    String::CPtr x = String::create("x");
    ASSERT_TRUE(m->put(x, 123).isUndefined());
    ASSERT_TRUE(m->get(x).equals(123));
    ASSERT_TRUE(m->get(String::create("x")).equals(123));

    ASSERT_TRUE(m->put(x, 456).equals(123));
    ASSERT_TRUE(m->get(x).equals(456));
//  ASSERT_TRUE(m->get(String::intern("x")).equals(456));
}

TEST(GTestConcurrentMap, TestPutAndGet2) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    ASSERT_TRUE(m->put(String::null(), 123).isUndefined());
    ASSERT_TRUE(m->get(String::null()).equals(123));
    ASSERT_TRUE(m->get(ConcurrentMap::null()).equals(123));

    ASSERT_TRUE(m->put(ConcurrentMap::null(), String::null()).equals(123));
    ASSERT_TRUE(m->get(String::null()).equals(ConcurrentMap::null()));

    ASSERT_TRUE(m->put(UNDEFINED, UNDEFINED).isUndefined());
    ASSERT_TRUE(m->get(UNDEFINED).isUndefined());
}

TEST(GTestConcurrentMap, TestKeySet) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    m->put(x, 123);
    m->put(y, 456);

    Set::CPtr ks = m->keySet();
    Iterator::Ptr itr = ks->iterator();
    ASSERT_TRUE(itr->hasNext());
    String::CPtr v1 = toCPtr<String>(itr->next());
    ASSERT_TRUE(v1->equals(x) || v1->equals(y));
    ASSERT_TRUE(itr->hasNext());
    String::CPtr v2 = toCPtr<String>(itr->next());
    ASSERT_TRUE(!v1->equals(v2) && (v2->equals(x) || v2->equals(y)));
    ASSERT_FALSE(itr->hasNext());
}

TEST(GTestConcurrentMap, TestContainsKey) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    m->put(x, 123);
    ASSERT_TRUE(m->containsKey(x));
    ASSERT_FALSE(m->containsKey(y));
    ASSERT_FALSE(m->containsKey(String::null()));

    m->put(String::null(), 456);
    ASSERT_TRUE(m->containsKey(String::null()));

    m->put(UNDEFINED, 789);
    ASSERT_TRUE(m->containsKey(UNDEFINED));
}

TEST(GTestConcurrentMap, TestContainsValue) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    String::CPtr z = String::create("z");
    m->put(x, 123);
    ASSERT_TRUE(m->containsValue(123));
    ASSERT_FALSE(m->containsValue(456));
    ASSERT_FALSE(m->containsValue(String::null()));

    m->put(y, String::null());
    ASSERT_TRUE(m->containsValue(String::null()));

    m->put(z, UNDEFINED);
    ASSERT_TRUE(m->containsValue(UNDEFINED));
}

TEST(GTestConcurrentMap, TestClear) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    m->put(x, 123);
    m->put(y, 456);
    m->put(String::null(), UNDEFINED);
    m->clear();
    ASSERT_TRUE(m->isEmpty());
}

TEST(GTestConcurrentMap, TestRemove) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    String::CPtr z = String::create("z");
    m->put(x, 123);
    m->put(y, String::null());
    m->put(String::null(), z);
    m->put(UNDEFINED, UNDEFINED);
    ASSERT_EQ(4, m->size());
    ASSERT_TRUE(m->remove(x).equals(123));
    ASSERT_EQ(3, m->size());
    ASSERT_TRUE(m->remove(y).equals(String::null()));
    ASSERT_EQ(2, m->size());
    ASSERT_TRUE(m->remove(String::null()).equals(z));
    ASSERT_EQ(1, m->size());
    ASSERT_TRUE(m->remove(UNDEFINED).isUndefined());
    ASSERT_TRUE(m->isEmpty());
}

TEST(GTestConcurrentMap, TestToString) {
    ConcurrentMap::Ptr m = ConcurrentMap::create();
    ASSERT_TRUE(m->toString()->equals(String::create("{}")));

    String::CPtr x = String::create("x");
    String::CPtr y = String::create("y");
    String::CPtr z = String::create("z");
    m->put(x, 123);
    m->put(y, String::null());
    m->put(String::null(), z);
    m->put(UNDEFINED, UNDEFINED);
    ASSERT_TRUE(m->toString()->equals(
        String::create("{undefined=undefined, null=z, x=123, y=null}")));
}

#ifdef LIBJ_USE_SP
TEST(GTestConcurrentMap, TestUseCount) {
    ConcurrentMap::CPtr p = ConcurrentMap::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
