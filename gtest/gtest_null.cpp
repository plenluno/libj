// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/null.h>

namespace libj {

TEST(GTestNull, TestToString) {
    Null::Ptr p = Null::instance();
    String::CPtr s = String::create("null");
    ASSERT_TRUE(s->equals(p->toString()));
}

TEST(GTestNull, TestInstanceOf) {
    Null::CPtr p = Null::instance();
    ASSERT_TRUE(p->instanceof(Type<Null>::id()));
    ASSERT_TRUE(p->instanceof(Type<Singleton>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
TEST(GTestNull, TestUseCount) {
    Null::CPtr p = Null::instance();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
