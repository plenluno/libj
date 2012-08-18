// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <json/json.h>
#include <string>

TEST(GTestJsonCpp, TestJsonCpp) {
    Json::Reader reader;
    Json::Value root;
    std::string jstr("{\"x\":123,\"y\":[3,false]}");
    std::istringstream is(jstr);
    reader.parse(is, root);
    ASSERT_TRUE(root.isObject());
    ASSERT_EQ(2, root.getMemberNames().size());
    ASSERT_EQ(0, root.getMemberNames()[0].compare("x"));
    ASSERT_EQ(0, root.getMemberNames()[1].compare("y"));
    ASSERT_EQ(123, root["x"].asInt());
    ASSERT_TRUE(root["y"].isArray());
    ASSERT_EQ(2, root["y"].size());
    ASSERT_EQ(3, root["y"][static_cast<Json::UInt>(0)].asInt());
    ASSERT_FALSE(root["y"][static_cast<Json::UInt>(1)].asBool());
}
