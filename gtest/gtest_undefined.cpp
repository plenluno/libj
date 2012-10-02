// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/undefined.h>

namespace libj {

TEST(GTestUndefined, TestInstance) {
    Undefined::Ptr p = Undefined::instance();
    ASSERT_TRUE(p);
    ASSERT_EQ(Type<Undefined>::id(), p->type());
}

TEST(GTestUndefined, TestNull) {
    Undefined::Ptr p = Undefined::null();
    ASSERT_FALSE(p);
}

TEST(GTestUndefined, TestToString) {
    String::CPtr s = String::create("undefined");
    ASSERT_TRUE(Undefined::instance()->toString()->equals(s));
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
