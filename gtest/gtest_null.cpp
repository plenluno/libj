// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/null.h>

namespace libj {

TEST(GTestNull, TestToString) {
    Null::Ptr p = Null::instance();
    String::CPtr s = String::create("null");
    ASSERT_EQ(s->compareTo(p->toString()), 0);
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
    ASSERT_EQ(p.use_count(), 1);
}
#endif

}  // namespace libj
