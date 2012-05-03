// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/json.h>
#include <libj/array_list.h>
#include <libj/map.h>
#include <libj/null.h>

namespace libj {

TEST(GTestJson, TestStringify) {
    Type<Json>::Ptr json = Json::instance();
    ASSERT_EQ(json->stringify(3)->compareTo(String::create("3")), 0);
    ASSERT_EQ(json->stringify(3.3)->compareTo(String::create("3.300000")), 0);
    ASSERT_EQ(json->stringify(true)->compareTo(String::create("true")), 0);
    ASSERT_EQ(json->stringify(false)->compareTo(String::create("false")), 0);
    ASSERT_EQ(json->stringify(Null::instance())->compareTo(String::create("null")), 0);
    ASSERT_EQ(json->stringify(String::create("456"))->compareTo(String::create("\"456\"")), 0);
    ASSERT_EQ(json->stringify(Map::create())->compareTo(String::create("{}")), 0);
    ASSERT_EQ(json->stringify(ArrayList::create())->compareTo(String::create("[]")), 0);
    
    Type<Map>::Ptr m = Map::create();
    m->put(3, false);
    m->put(String::create("x"), 123);
    m->put(String::create("y"), String::create("456"));
    ASSERT_EQ(json->stringify(m)->compareTo(String::create("{\"x\":123,\"y\":\"456\"}")), 0);
    
    Type<ArrayList>::Ptr a = ArrayList::create();
    a->add(3);
    a->add(false);
    ASSERT_EQ(json->stringify(a)->compareTo(String::create("[3,false]")), 0);
}

}  // namespace libj
