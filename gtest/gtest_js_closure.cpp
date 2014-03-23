// Copyright (c) 2012-2014 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/error.h>
#include <libj/js_closure.h>

namespace libj {

TEST(GTestJsClosure, TestClosure) {
    JsClosure::Ptr add = JsClosure::create(
        [] (JsArray::Ptr args) -> Value {
        if (!args) {
            return Error::create(Error::ILLEGAL_ARGUMENT);
        }

        Int sum = 0;
        for (Size i = 0; i < args->length(); i++) {
            int x;
            if (to<Int>(args->get(i), &x)) {
                sum += x;
            } else {
                return Error::create(Error::ILLEGAL_ARGUMENT);
            }
        }
        return sum;
    });

    JsArray::Ptr args = JsArray::create();
    args->add(3);
    args->add(4);
    ASSERT_TRUE((*add)(args).equals(7));

    ASSERT_TRUE(add->call().instanceof(Type<Error>::id()));
    ASSERT_TRUE(add->call(1).equals(1));
    ASSERT_TRUE(add->call(1, 2).equals(3));
    ASSERT_TRUE(add->call(1, 2, 3).equals(6));
    ASSERT_TRUE(add->call(1, 2, 3, 4).equals(10));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5).equals(15));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6).equals(21));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6, 7).equals(28));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6, 7, 8).equals(36));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6, 7, 8, 9).equals(45));
}

TEST(GTestJsClosure, TestClosure2) {
    String::CPtr abc = String::create("abc");
    String::CPtr xyz = String::create("xyz");

    JsClosure::Ptr concat = JsClosure::create(
        [abc, xyz] (JsArray::Ptr args) -> Value {
        return abc->concat(xyz);
    });

    ASSERT_TRUE(concat->call().equals(String::create("abcxyz")));
}

TEST(GTestJsClosure, TestInstanceOf) {
    JsClosure::Ptr c = JsClosure::create(
        [] (JsArray::Ptr args) { return UNDEFINED; }
    );

    ASSERT_TRUE(c->instanceof(Type<JsClosure>::id()));
    ASSERT_TRUE(c->instanceof(Type<JsFunction>::id()));
    ASSERT_TRUE(c->instanceof(Type<Function>::id()));
    ASSERT_TRUE(c->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(c->instanceof(Type<Object>::id()));

    ASSERT_FALSE(c->instanceof(Type<Immutable>::id()));
}

}  // namespace libj
