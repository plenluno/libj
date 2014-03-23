// Copyright (c) 2012-2014 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/error.h>
#include <libj/mutable.h>

namespace libj {

TEST(GTestError, TestCreate) {
    Error::CPtr e = Error::create(Error::ANY);
    ASSERT_TRUE(!!e);
}

TEST(GTestError, TestMessage) {
    Error::CPtr e = Error::create(Error::TIMEOUT);
    String::CPtr strTimeout = String::create("Timeout");
    ASSERT_TRUE(e->message()->equals(strTimeout));
}

TEST(GTestError, TestMessage2) {
    String::CPtr foo = String::create("foo");
    Error::CPtr e = Error::create(Error::ANY, foo);
    ASSERT_TRUE(e->message()->equals(foo));
}

TEST(GTestError, TestToString) {
    String::CPtr foo = String::create("foo");
    Error::CPtr e = Error::create(Error::ANY, foo);
    ASSERT_TRUE(e->toString()->equals(foo));
}

TEST(GTestError, TestInstanceOf) {
    Error::CPtr e = Error::create(Error::ANY);
    ASSERT_TRUE(e->instanceof(Type<Error>::id()));
    ASSERT_TRUE(e->instanceof(Type<Status>::id()));
    ASSERT_TRUE(e->instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(e->instanceof(Type<Object>::id()));

    ASSERT_FALSE(e->instanceof(Type<Mutable>::id()));
}

}  // namespace libj
