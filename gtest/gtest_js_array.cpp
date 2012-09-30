// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_array.h>
#include <libj/error.h>
#include <libj/string.h>

namespace libj {

TEST(GTestJsArray, TestCreate) {
    JsArray::Ptr a = JsArray::create();
    ASSERT_TRUE(!!a);
}

TEST(GTestJsArray, TestCreate2) {
    ASSERT_FALSE(JsArray::create(ArrayList::null()));

    ArrayList::Ptr a = ArrayList::create();
    a->add(3);
    a->add(String::create("abc"));
    JsArray::Ptr ja = JsArray::create(a);
    ASSERT_EQ(2, ja->size());
    Int i;
    ASSERT_TRUE(to<Int>(ja->get(0), &i));
    ASSERT_EQ(3, i);
    ASSERT_TRUE(ja->get(1).equals(String::create("abc")));
}

TEST(GTestJsArray, TestInstanceOf) {
    JsArray::Ptr a = JsArray::create();
    ASSERT_TRUE(a->instanceof(Type<JsArray>::id()));
    ASSERT_TRUE(a->instanceof(Type<List>::id()));
    ASSERT_TRUE(a->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(a->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceof(Type<Object>::id()));
}

TEST(GTestJsArray, TestInstanceOf2) {
    JsArray::CPtr a = JsArray::create();
    ASSERT_TRUE(a->instanceof(Type<JsArray>::id()));
    ASSERT_TRUE(a->instanceof(Type<List>::id()));
    ASSERT_TRUE(a->instanceof(Type<Collection>::id()));
    ASSERT_TRUE(a->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(a->instanceof(Type<Object>::id()));
}

TEST(GTestJsArray, TestToString) {
    JsArray::Ptr a = JsArray::create();
    a->add(1);
    JsArray::Ptr a2 = JsArray::create();
    a2->add(3);
    a2->add(5);
    a->add(a2);
    a->add(7);
    ASSERT_TRUE(a->toString()->equals(String::create("1,3,5,7")));
}

TEST(GTestJsArray, TestSubList) {
    JsArray::Ptr a = JsArray::create();
    a->add(3);
    a->add(5);
    a->add(7);

    JsArray::Ptr sub1 = toPtr<JsArray>(a->subList(1, 2));
    ASSERT_TRUE(sub1->toString()->equals(String::create("5")));

    JsArray::Ptr sub2 = toPtr<JsArray>(a->subList(0, 3));
    ASSERT_TRUE(sub2->toString()->equals(String::create("3,5,7")));

    JsArray::Ptr sub3 = toPtr<JsArray>(a->subList(2, 2));
    ASSERT_TRUE(sub3->toString()->equals(String::create("")));

#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(a->subList(0, 4));
    ASSERT_ANY_THROW(a->subList(2, 1));
#else
    ASSERT_EQ(
        Error::INDEX_OUT_OF_BOUNDS,
        toCPtr<Error>(a->subList(0, 4))->code());
    ASSERT_EQ(
        Error::INDEX_OUT_OF_BOUNDS,
        toCPtr<Error>(a->subList(2, 1))->code());
#endif  // LIBJ_USE_EXCEPTION
}

TEST(GTestJsArray, TestJsProperty) {
    JsArray::Ptr a = JsArray::create();
    a->setProperty(String::create("abc"), 7);
    ASSERT_TRUE(a->hasProperty(String::create("abc")));
    ASSERT_TRUE(a->getProperty(String::create("abc")).equals(7));

    a->deleteProperty(String::create("abc"));
    ASSERT_FALSE(a->hasProperty(String::create("abc")));
}

#ifdef LIBJ_USE_SP
TEST(GTestJsArray, TestUseCount) {
    JsArray::CPtr p = JsArray::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
