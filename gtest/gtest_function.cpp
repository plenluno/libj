// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/function.h>
#include <libj/error.h>

namespace libj {

class Add : LIBJ_FUNCTION(Add)
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
        return String::create("Add");
    }

    static Add::Ptr create() {
        Add::Ptr p(new Add());
        return p;
    }
};

TEST(GTestFunction, TestFunctor) {
    Function::Ptr add = Add::create();
    ArrayList::Ptr args = ArrayList::create();
    args->add(2);
    args->add(3);
    Value sum = (*add)(args);
    Int s;
    to<Int>(sum, &s);
    ASSERT_EQ(s, 5);
}

TEST(GTestFunction, TestCall) {
    Function::Ptr add = Add::create();
    Value sum = add->call(4, 5);
    Int s;
    to<Int>(sum, &s);
    ASSERT_EQ(s, 9);
}

#ifdef LIBJ_USE_SP
TEST(GTestFunction, TestUseCount) {
    Function::CPtr p = Add::create();
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
