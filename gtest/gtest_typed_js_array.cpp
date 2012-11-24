// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/typed_js_array.h>
#include <libj/typed_array_list.h>

namespace libj {

TEST(GTestTypedJsArray, TestCreate) {
    TypedJsArray<Int>::Ptr a = TypedJsArray<Int>::create();
    ASSERT_TRUE(!!a);
}

TEST(GTestTypedJsArray, TestCreate2) {
    JsArray::Ptr a = JsArray::create();
    a->add(5);
    TypedJsArray<Int>::Ptr ta =
        TypedJsArray<Int>::create(a);
    ASSERT_TRUE(!!ta);

    a->add(7.7);
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(TypedJsArray<Int>::create(a));
#else
    ta = TypedJsArray<Int>::create(a);
    ASSERT_FALSE(!!ta);
#endif  // LIBJ_USE_EXCEPTION
}


TEST(GTestTypedJsArray, TestAdd) {
    TypedJsArray<Int>::Ptr a = TypedJsArray<Int>::create();
#ifdef LIBJ_USE_EXCEPTION
    ASSERT_ANY_THROW(a->add(5.5));
#else
    ASSERT_FALSE(a->add(5.5));
#endif  // LIBJ_USE_EXCEPTION

    ASSERT_TRUE(a->add(5));
    ASSERT_TRUE(a->add(7));
    ASSERT_EQ(2, a->length());
}

TEST(GTestTypedJsArray, TestGet) {
    TypedJsArray<Int>::Ptr a = TypedJsArray<Int>::create();
    ASSERT_TRUE(a->add(5));
    ASSERT_TRUE(a->add(7));
    ASSERT_TRUE(a->get(0).equals(5));
    ASSERT_TRUE(a->get(1).equals(7));
}

TEST(GTestTypedJsArray, TestGetTyped) {
    TypedJsArray<Int>::Ptr a = TypedJsArray<Int>::create();
    ASSERT_TRUE(a->addTyped(9));
    ASSERT_TRUE(a->addTyped(11));
    ASSERT_EQ(9, a->getTyped(0));
    ASSERT_EQ(11, a->getTyped(1));
}

TEST(GTestTypedJsArray, TestJsProperty) {
    TypedJsArray<Int>::Ptr a = TypedJsArray<Int>::create();
    a->setProperty(String::create("abc"), 7);
    ASSERT_TRUE(a->hasProperty(String::create("abc")));
    ASSERT_TRUE(a->getProperty(String::create("abc")).equals(7));

    a->deleteProperty(String::create("abc"));
    ASSERT_FALSE(a->hasProperty(String::create("abc")));
}

TEST(GTestTypedJsArray, TestSubList) {
    TypedJsArray<Int>::Ptr a = TypedJsArray<Int>::create();
    a->add(3);
    a->add(5);
    a->add(7);

    TypedJsArray<Int>::Ptr sub1 = toPtr<TypedJsArray<Int> >(a->subList(1, 2));
    ASSERT_TRUE(sub1 && sub1->toString()->equals(String::create("5")));

    TypedJsArray<Int>::Ptr sub2 = toPtr<TypedJsArray<Int> >(a->subList(0, 3));
    ASSERT_TRUE(sub2 && sub2->toString()->equals(String::create("3,5,7")));

    TypedJsArray<Int>::Ptr sub3 = toPtr<TypedJsArray<Int> >(a->subList(2, 2));
    ASSERT_TRUE(sub3 && sub3->toString()->equals(String::create()));

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

TEST(GTestTypedJsArray, TestSubarray) {
    TypedJsArray<Int>::Ptr a = TypedJsArray<Int>::create();
    a->add(3);
    a->add(5);
    a->add(7);

    TypedJsArray<Int>::Ptr sub1 = toPtr<TypedJsArray<Int> >(a->subarray(1, 2));
    ASSERT_TRUE(sub1 && sub1->toString()->equals(String::create("5")));

    TypedJsArray<Int>::Ptr sub2 = toPtr<TypedJsArray<Int> >(a->subarray(0, 3));
    ASSERT_TRUE(sub2 && sub2->toString()->equals(String::create("3,5,7")));

    TypedJsArray<Int>::Ptr sub3 = toPtr<TypedJsArray<Int> >(a->subarray(2, 2));
    ASSERT_TRUE(sub3 && sub3->toString()->equals(String::create()));

    TypedJsArray<Int>::Ptr sub4 = toPtr<TypedJsArray<Int> >(a->subarray(0, 4));
    ASSERT_TRUE(sub4 && sub4->toString()->equals(String::create("3,5,7")));

    TypedJsArray<Int>::Ptr sub5 = toPtr<TypedJsArray<Int> >(a->subarray(2, 1));
    ASSERT_TRUE(sub5 && sub5->toString()->equals(String::create()));
}

}  // namespace libj
