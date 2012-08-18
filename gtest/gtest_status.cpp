// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/status.h>

namespace libj {

TEST(GTestStatus, TestCreate) {
    Status::CPtr s = Status::create(Status::OK);
    ASSERT_TRUE(s);
}

TEST(GTestStatus, TestMessage) {
    Status::CPtr s = Status::create(Status::OK);
    String::CPtr ok = String::create("OK");
    ASSERT_TRUE(s->message()->equals(ok));
}

TEST(GTestStatus, TestToString) {
    Status::CPtr s = Status::create(Status::OK);
    String::CPtr ok = String::create("OK");
    ASSERT_TRUE(s->toString()->equals(ok));
}

TEST(GTestStatus, TestInstanceOf) {
    Status::CPtr s = Status::create(Status::OK);
    ASSERT_TRUE(s->instanceof(Type<Status>::id()));
    ASSERT_TRUE(s->instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(s->instanceof(Type<Object>::id()));
}

}  // namespace libj
