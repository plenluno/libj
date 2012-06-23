// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/error.h>

namespace libj {

TEST(GTestError, TestCreate) {
    Error::CPtr e = Error::create(Status::OK);
    ASSERT_FALSE(e);
    e = Error::create(Error::ANY);
    ASSERT_TRUE(e);
}

TEST(GTestError, TestMessage) {
    Error::CPtr e = Error::create(Error::TIMEOUT);
    String::CPtr strTimeout = String::create("Timeout");
    ASSERT_EQ(e->message()->compareTo(strTimeout), 0);
}

TEST(GTestError, TestMessage2) {
    String::CPtr foo = String::create("foo");
    Error::CPtr e = Error::create(Error::ANY, foo);
    ASSERT_EQ(e->message()->compareTo(foo), 0);
}

TEST(GTestError, TestToString) {
    String::CPtr foo = String::create("foo");
    Error::CPtr e = Error::create(Error::ANY, foo);
    ASSERT_EQ(e->toString()->compareTo(foo), 0);
}

TEST(GTestError, TestInstanceOf) {
    Error::CPtr e = Error::create(Error::ANY);
    ASSERT_TRUE(e->instanceof(Type<Error>::id()));
    ASSERT_TRUE(e->instanceof(Type<Status>::id()));
    ASSERT_TRUE(e->instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(e->instanceof(Type<Object>::id()));
}

}  // namespace libj
