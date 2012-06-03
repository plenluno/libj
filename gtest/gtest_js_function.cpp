// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/js_function.h>
#include <libj/error.h>

#include <libj/console.h>

namespace libj {

class GTestJsFunctionAdd : LIBJ_JS_FUNCTION(GTestJsFunctionAdd)
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

    static GTestJsFunctionAdd::Ptr create() {
        GTestJsFunctionAdd::Ptr p(new GTestJsFunctionAdd());
        return p;
    }
};

TEST(GTestJsFunction, TestToString) {
    GTestJsFunctionAdd::Ptr add = GTestJsFunctionAdd::create();
    ASSERT_EQ(add->toString()->compareTo(
        String::create("function GTestJsFunctionAdd() {}")), 0);
}

}  // namespace libj
