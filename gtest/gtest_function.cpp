// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/function.h>
#include <libj/error.h>

namespace libj {

class Add : LIBJ_FUNCTION(Add)
};

class AddImpl : public Add {
 public:
    Value operator()(Type<ArrayList>::Cptr args) {
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
    
    static Type<Add>::Ptr create() {
        Type<Add>::Ptr p(new AddImpl());
        return p;
    }
};

Type<Add>::Ptr Add::create() {
    return AddImpl::create();
}

TEST(GTestFunction, TestAdd) {
    Type<Function>::Ptr add = Add::create();
    Type<ArrayList>::Ptr args = ArrayList::create();
    args->add(2);
    args->add(3);
    Value sum = (*add)(args);
    Int s;
    to<Int>(sum, &s);
    ASSERT_EQ(s, 5);
}

}