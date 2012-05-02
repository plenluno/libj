// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/value.h>
#include <libj/mutable.h>
#include <libj/string.h>
#include <boost/any.hpp>

namespace libj {

#ifdef LIBJ_GTEST_BUILD_ERRORS
// #define LIBJ_GTEST_VALUE_BUILD_ERRORS
#endif

#ifdef LIBJ_GTEST_VALUE_BUILD_ERRORS
TEST(GTestValue, Error) {
    const Value v = 3;
    v = 5;
}

TEST(GTestAny, Error) {
    const boost::any a = 3;
    a = 5;
}

#if 0
// OK
TEST(GTestValue, Error2) {
    const Value v = 3;
    int i;
    int& ir = i;
    ASSERT_TRUE(to<int&>(v, &ir));
    ASSERT_EQ(ir, 3);
}
#endif

TEST(GTestAny, Error2) {
    const boost::any a = 3;
    int i;
    int& ir = i;
    ir = boost::any_cast<int&>(a);
}

TEST(GTestValue, Error3) {
    int* ip;
    Value v = 5;
    Value* vp = &v;
    to<const int>(vp, &ip);
}

TEST(GTestAny, Error3) {
    boost::any a = 5;
    boost::any* ap = &a;
    int* ip = boost::any_cast<const int>(ap);
}

TEST(GTestValue, Error4) {
    Value v = 3;
    const Value* vp = &v;
    int* ip;
    ASSERT_TRUE(to<int>(vp, &ip));
    ASSERT_EQ(*ip, 3);
}

TEST(GTestAny, Error4) {
    boost::any a = 3;
    const boost::any* ap = &a;
    int* ip  = boost::any_cast<int>(ap);
    ASSERT_EQ(*ip, 3);
}
#endif

TEST(GTestValue, Test) {
    Value v = 3;
    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(i, 3);

    v = 5;
    ASSERT_TRUE(to<const int>(v, &i));
    ASSERT_EQ(i, 5);

    int64_t l;
    ASSERT_FALSE(to<int64_t>(v, &l));
}

TEST(GTestAny, Test) {
    boost::any a = 3;
    int i = boost::any_cast<int>(a);
    ASSERT_EQ(i, 3);

    a = 5;
    i = boost::any_cast<const int>(a);
    ASSERT_EQ(i, 5);

    ASSERT_ANY_THROW(int64_t l = boost::any_cast<int64_t>(a));
}

TEST(GTestValue, Test2) {
    const int ci = 5;
    Value v = ci;

    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(i, 5);
}

TEST(GTestAny, Test2) {
    const int ci = 5;
    boost::any a = ci;

    int i = boost::any_cast<int>(a);
    ASSERT_EQ(i, 5);
}

TEST(GTestValue, Test3) {
    int i = 9;
    Value v = &i;

    int* ip;
    ASSERT_TRUE(to<int*>(v, &ip));
    ASSERT_EQ(ip, &i);

    const int* cip;
    ASSERT_FALSE(to<const int*>(v, &cip));
}

TEST(GTestAny, Test3) {
    int i = 9;
    boost::any a = &i;

    int* ip = boost::any_cast<int*>(a);
    ASSERT_EQ(ip, &i);

    ASSERT_ANY_THROW(const int* cip = boost::any_cast<const int*>(a));
}

TEST(GTestValue, Test4) {
    const int i = 11;
    Value v = &i;

    int* ip;
    ASSERT_FALSE(to<int*>(v, &ip));

    const int* cip;
    ASSERT_TRUE(to<const int*>(v, &cip));
    ASSERT_EQ(cip, &i);
}

TEST(GTestAny, Test4) {
    const int i = 11;
    boost::any a = &i;

    ASSERT_ANY_THROW(int* ip = boost::any_cast<int*>(a));

    const int* cip = boost::any_cast<const int*>(a);
    ASSERT_EQ(cip, &i);
}

TEST(GTestValue, Test5) {
    Value v = 3;

    int i;
    int& ir = i;
    ASSERT_TRUE(to<int&>(v, &ir));
    ASSERT_EQ(ir, 3);

    v = 5;
    ASSERT_TRUE(to<const int&>(v, &ir));
    ASSERT_EQ(ir, 5);

    int64_t l;
    int64_t& lr = l;
    ASSERT_FALSE(to<int64_t&>(v, &lr));
}

TEST(GTestAny, Test5) {
    boost::any a = 3;

    int i;
    int& ir = i;
    ir = boost::any_cast<int&>(a);
    ASSERT_EQ(ir, 3);

    a = 5;
    ir = boost::any_cast<const int&>(a);
    ASSERT_EQ(ir, 5);

    int64_t l;
    int64_t& lr = l;
    ASSERT_ANY_THROW(lr = boost::any_cast<int64_t&>(a));
}

TEST(GTestValue, Test6) {
    const Value v = 3;

    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(i, 3);

    ASSERT_TRUE(to<const int>(v, &i));
    ASSERT_EQ(i, 3);

    int64_t l;
    ASSERT_FALSE(to<int64_t>(v, &l));
}

TEST(GTestAny, Test6) {
    const boost::any a = 3;

    int i = boost::any_cast<int>(a);
    ASSERT_EQ(i, 3);

    i = boost::any_cast<const int>(a);
    ASSERT_EQ(i, 3);

    ASSERT_ANY_THROW(int64_t l = boost::any_cast<int64_t>(a));
}

TEST(GTestValue, Test7) {
    const Value v = 3;
    int i;
    int& ir = i;
    ASSERT_TRUE(to<const int&>(v, &ir));
    ASSERT_EQ(ir, 3);
}

TEST(GTestAny, Test7) {
    const boost::any a = 3;
    int i;
    int& ir = i;
    ir = boost::any_cast<const int&>(a);
    ASSERT_EQ(ir, 3);
}

TEST(GTestValue, Test8) {
    Value v = 3;
    Value* vp = &v;

    int* ip;
    ASSERT_TRUE(to<int>(vp, &ip));
    ASSERT_EQ(*ip, 3);

    int64_t* lp;
#if 1
    ASSERT_FALSE(to<int64_t>(vp, &lp));
#else
    ASSERT_TRUE(to<int64_t>(vp, &lp));
    ASSERT_EQ(*lp, 3);
#endif
}

TEST(GTestAny, Test8) {
    boost::any a = 3;
    boost::any* ap = &a;

    int* ip  = boost::any_cast<int>(ap);
    ASSERT_EQ(*ip, 3);

//  Segmentation fault
//  int64_t* lp = boost::any_cast<int64_t>(ap);
//  ASSERT_EQ(*lp, 3);
}

TEST(GTestValue, Test9) {
    Value v = 3;
    const Value* vp = &v;

    const int* ip;
    ASSERT_TRUE(to<int>(vp, &ip));
    ASSERT_EQ(*ip, 3);

    v = 5;
    ASSERT_TRUE(to<const int>(vp, &ip));
    ASSERT_EQ(*ip, 5);
}

TEST(GTestAny, Test9) {
    boost::any a = 3;
    const boost::any* ap = &a;

    const int* ip = boost::any_cast<int>(ap);
    ASSERT_EQ(*ip, 3);

    a = 5;
    ip = boost::any_cast<const int>(ap);
    ASSERT_EQ(*ip, 5);
}

TEST(GTestValue, TestInstanceOf) {
    Type<String>::Cptr s = String::create("abc");
    Value v = s;
    ASSERT_TRUE(v.instanceOf(Type<String>::id()));
    ASSERT_FALSE(v.instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(v.instanceOf(Type<Immutable>::id()));
    ASSERT_TRUE(v.instanceOf(Type<Object>::id()));
    ASSERT_FALSE(v.instanceOf(Type<int>::id()));
    
    v = 1;
    ASSERT_FALSE(v.instanceOf(Type<Object>::id()));
    ASSERT_FALSE(v.instanceOf(Type<int>::id()));
}

}  // namespace libj
