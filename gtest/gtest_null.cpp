// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/null.h>

namespace libj {

TEST(GTestNull, TestToString) {
    Type<Null>::Ptr p = Null::instance();
    Type<String>::Cptr s = String::create("null");
    ASSERT_EQ(s->compareTo(p->toString()), 0);
}

TEST(GTestNull, TestInstanceOf) {
    Type<Null>::Cptr p = Null::instance();
    ASSERT_TRUE(p->instanceOf(Type<Null>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Singleton>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Object>::id()));
}

}  // namespace libj
