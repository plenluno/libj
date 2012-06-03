// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <boost/any.hpp>
#include <libj/array_list.h>
#include <libj/null.h>
#include <libj/string.h>
#include <libj/value.h>

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

    ASSERT_ANY_THROW(boost::any_cast<int64_t>(a));
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

    ASSERT_ANY_THROW(boost::any_cast<const int*>(a));
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

    ASSERT_ANY_THROW(boost::any_cast<int*>(a));

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

    ASSERT_ANY_THROW(boost::any_cast<int64_t>(a));
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
    String::CPtr s = String::create("abc");
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

TEST(GTestValue, TestSingletonToPtrAndCPtr) {
    Null::Ptr null = Null::instance();
    Null::CPtr cnull = Null::instance();
    String::CPtr str = String::create("null");

    Value v = null;

    Null::Ptr n = toPtr<Null>(v);
    ASSERT_EQ(n->toString()->compareTo(str), 0);
    Null::CPtr cn = toCPtr<Null>(v);
    ASSERT_EQ(cn->toString()->compareTo(str), 0);
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_EQ(co->toString()->compareTo(str), 0);
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    Immutable::CPtr ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    Singleton::Ptr s = toPtr<Singleton>(v);
    ASSERT_EQ(s->toString()->compareTo(str), 0);
    Singleton::CPtr cs = toCPtr<Singleton>(v);
    ASSERT_EQ(cs->toString()->compareTo(str), 0);

    v = cnull;

    n = toPtr<Null>(v);
    ASSERT_FALSE(n);
    cn = toCPtr<Null>(v);
    ASSERT_EQ(cn->toString()->compareTo(str), 0);
    co = toCPtr<Object>(v);
    ASSERT_EQ(co->toString()->compareTo(str), 0);
    m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    s = toPtr<Singleton>(v);
    ASSERT_FALSE(s);
    cs = toCPtr<Singleton>(v);
    ASSERT_EQ(cs->toString()->compareTo(str), 0);
}

TEST(GTestValue, TestMutableToPtrAndCPtr) {
    ArrayList::Ptr arr = ArrayList::create();
    ArrayList::CPtr carr = arr;
    arr->add(1);
    arr->add(2);

    Value v = arr;

    ArrayList::Ptr a = toPtr<ArrayList>(v);
    ASSERT_EQ(a->size(), 2);
    ArrayList::CPtr ca = toCPtr<ArrayList>(v);
    ASSERT_EQ(ca->size(), 2);
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_EQ(co->type(), Type<ArrayList>::id());
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_EQ(m->type(), Type<ArrayList>::id());
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_EQ(cm->type(), Type<ArrayList>::id());
    Immutable::CPtr ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    Singleton::Ptr s = toPtr<Singleton>(v);
    ASSERT_FALSE(s);
    Singleton::CPtr cs = toCPtr<Singleton>(v);
    ASSERT_FALSE(cs);

    v = carr;

    a = toPtr<ArrayList>(v);
    ASSERT_FALSE(a);
    ca = toCPtr<ArrayList>(v);
    ASSERT_EQ(ca->type(), Type<ArrayList>::id());
    co = toCPtr<Object>(v);
    ASSERT_EQ(co->type(), Type<ArrayList>::id());
    m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    cm = toCPtr<Mutable>(v);
    ASSERT_EQ(cm->type(), Type<ArrayList>::id());
    ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    s = toPtr<Singleton>(v);
    ASSERT_FALSE(s);
    cs = toCPtr<Singleton>(v);
    ASSERT_FALSE(cs);
}


TEST(GTestValue, TestImmutableToCPtr) {
    String::CPtr str = String::create("abc");
    Value v = str;

    String::CPtr x = toCPtr<String>(v);
    ASSERT_EQ(x->compareTo(str), 0);
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_EQ(co->toString()->compareTo(str), 0);
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    Immutable::CPtr ci = toCPtr<Immutable>(v);
    ASSERT_EQ(ci->toString()->compareTo(str), 0);
    Singleton::Ptr s = toPtr<Singleton>(v);
    ASSERT_FALSE(s);
    Singleton::CPtr cs = toCPtr<Singleton>(v);
    ASSERT_FALSE(cs);
}

TEST(GTestValue, TestCompareTo) {
    Value v1 = 5;
    Value v2 = 10;
    Value v3 = 5;
    Value v4 = (Long)5;

    ASSERT_LT(v1.compareTo(v2), 0);
    ASSERT_GT(v2.compareTo(v1), 0);
    ASSERT_EQ(v1.compareTo(v3), 0);
    ASSERT_NE(v1.compareTo(v4), 0);
}

struct GTestValueStruct {};

TEST(GTestValue, TestType) {
    int i = 3;
    Value v1 = i;
    const Value v2 = v1;
    Value v3 = v2;
    ASSERT_EQ(v3.type(), Type<int>::id());

    GTestValueStruct x;
    GTestValueStruct* y;

    Value v4 = &x;
    const Value& v5 = v4;
    const Value v6 = v5;
    ASSERT_EQ(v6.type(), Type<GTestValueStruct*>::id());
    ASSERT_TRUE(to<GTestValueStruct*>(v6, &y));
    ASSERT_EQ(y, &x);
}

}  // namespace libj
