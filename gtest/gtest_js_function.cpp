// Copyright (c) 2012-2014 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/error.h>
#include <libj/js_function.h>

namespace libj {

class GTestJsFunctionAdd : LIBJ_JS_FUNCTION(GTestJsFunctionAdd)
 public:
    Value operator()(JsArray::Ptr args) {
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
    }

    static GTestJsFunctionAdd::Ptr create() {
        return Ptr(new GTestJsFunctionAdd());
    }
};

class GTestJsFunctionAddx2 : public GTestJsFunctionAdd {
 public:
    Value operator()(JsArray::Ptr args) {
        Value val = GTestJsFunctionAdd::operator()(args);
        Int sum;
        if (to<Int>(val, &sum)) {
            return sum * 2;
        } else {
            return val;
        }
    }

    static Ptr create() {
        return Ptr(new GTestJsFunctionAddx2());
    }
};

TEST(GTestJsFunction, TestToString) {
    GTestJsFunctionAdd::Ptr add = GTestJsFunctionAdd::create();
    ASSERT_TRUE(add->toString()->equals(
        String::create("function GTestJsFunctionAdd() {}")));
}

TEST(GTestJsFunction, TestFunctor) {
    GTestJsFunctionAdd::Ptr add = GTestJsFunctionAdd::create();
    GTestJsFunctionAdd::Ptr addx2 = GTestJsFunctionAddx2::create();

    JsArray::Ptr args = JsArray::create();
    args->add(3);
    args->add(4);
    ASSERT_TRUE((*add)(args).equals(7));
    ASSERT_TRUE((*addx2)(args).equals(14));
}

TEST(GTestJsFunction, TestCall) {
    GTestJsFunctionAdd::Ptr add = GTestJsFunctionAdd::create();
    GTestJsFunctionAdd::Ptr addx2 = GTestJsFunctionAddx2::create();

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
    ASSERT_TRUE(addx2->call(1, 2, 3, 4, 5, 6, 7, 8, 9).equals(90));
}

TEST(GTestJsFunction, TestCompreTo) {
    GTestJsFunctionAdd::Ptr add1 = GTestJsFunctionAdd::create();
    GTestJsFunctionAdd::Ptr add2 = GTestJsFunctionAdd::create();
    ASSERT_EQ(0, add1->compareTo(add1));
    ASSERT_NE(0, add1->compareTo(add2));
}

TEST(GTestJsFunction, TestInstanceOf) {
    JsFunction::Ptr add = GTestJsFunctionAdd::create();
    ASSERT_TRUE(add->instanceof(Type<GTestJsFunctionAdd>::id()));
    ASSERT_TRUE(add->instanceof(Type<JsFunction>::id()));
    ASSERT_TRUE(add->instanceof(Type<Function>::id()));
    ASSERT_TRUE(add->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(add->instanceof(Type<Object>::id()));

    ASSERT_FALSE(add->instanceof(Type<Immutable>::id()));
}

}  // namespace libj
