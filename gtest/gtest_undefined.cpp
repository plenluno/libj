// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/undefined.h>

namespace libj {

TEST(GTestUndefined, TestToString) {
    Undefined::Ptr p = Undefined::instance();
    String::CPtr s = String::create("undefined");
    ASSERT_TRUE(s->equals(p->toString()));
}

TEST(GTestUndefined, TestInstanceOf) {
    Undefined::CPtr p = Undefined::instance();
    ASSERT_TRUE(p->instanceof(Type<Undefined>::id()));
    ASSERT_TRUE(p->instanceof(Type<Singleton>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
TEST(GTestUndefined, TestUseCount) {
    Undefined::CPtr p = Undefined::instance();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
