// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <json/json.h>

TEST(GTestJsonCpp, TestJsonCpp) {
    Json::Reader reader;
    Json::Value root;
    std::string jstr("{\"x\":123,\"y\":[3,false]}");
    std::istringstream is(jstr);
    reader.parse(is, root);
    ASSERT_TRUE(root.isObject());
    ASSERT_EQ(root.getMemberNames().size(), 2);
    ASSERT_EQ(root.getMemberNames()[0].compare("x"), 0);
    ASSERT_EQ(root.getMemberNames()[1].compare("y"), 0);
    ASSERT_EQ(root["x"].asInt(), 123);
    ASSERT_TRUE(root["y"].isArray());
    ASSERT_EQ(root["y"].size(), 2);
    ASSERT_EQ(root["y"][static_cast<Json::UInt>(0)].asInt(), 3);
    ASSERT_EQ(root["y"][static_cast<Json::UInt>(1)].asBool(), false);
}
