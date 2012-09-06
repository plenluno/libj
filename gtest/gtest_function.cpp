// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/error.h>
#include <libj/function.h>

namespace libj {

class GTestFunctionAdd : LIBJ_FUNCTION(GTestFunctionAdd)
 public:
    Value operator()(ArrayList::Ptr args) {
        if (args->size() == 2 &&
            args->get(0).type() == Type<Int>::id() &&
            args->get(1).type() == Type<Int>::id()) {
            int x, y;
            to<Int>(args->get(0), &x);
            to<Int>(args->get(1), &y);
            return x + y;
        } else {
            return Error::create(Error::ILLEGAL_ARGUMENT);
        }
    }

    String::CPtr toString() const {
        return String::create();
    }

    static GTestFunctionAdd::Ptr create() {
        GTestFunctionAdd::Ptr p(new GTestFunctionAdd());
        return p;
    }
};

TEST(GTestFunction, TestFunctor) {
    Function::Ptr add = GTestFunctionAdd::create();
    ArrayList::Ptr args = ArrayList::create();
    args->add(2);
    args->add(3);
    Value sum = (*add)(args);
    Int s;
    to<Int>(sum, &s);
    ASSERT_EQ(5, s);
}

TEST(GTestFunction, TestCall) {
    Function::Ptr add = GTestFunctionAdd::create();
    Value sum = add->call(4, 5);
    Int s;
    to<Int>(sum, &s);
    ASSERT_EQ(9, s);
}

#ifdef LIBJ_USE_SP
TEST(GTestFunction, TestUseCount) {
    Function::CPtr p = GTestFunctionAdd::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
