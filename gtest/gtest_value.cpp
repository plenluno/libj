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
    ASSERT_EQ(3, ir);
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
    ASSERT_EQ(3, *ip);
}

TEST(GTestAny, Error4) {
    boost::any a = 3;
    const boost::any* ap = &a;
    int* ip  = boost::any_cast<int>(ap);
    ASSERT_EQ(3, *ip);
}
#endif

TEST(GTestValue, Test) {
    Value v = 3;
    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(3, i);

    v = 5;
    ASSERT_TRUE(to<const int>(v, &i));
    ASSERT_EQ(5, i);

    int64_t l;
    ASSERT_FALSE(to<int64_t>(v, &l));
}

TEST(GTestAny, Test) {
    boost::any a = 3;
    int i = boost::any_cast<int>(a);
    ASSERT_EQ(3, i);

    a = 5;
    i = boost::any_cast<const int>(a);
    ASSERT_EQ(5, i);

    ASSERT_ANY_THROW(boost::any_cast<int64_t>(a));
}

TEST(GTestValue, Test2) {
    const int ci = 5;
    Value v = ci;

    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(5, i);
}

TEST(GTestAny, Test2) {
    const int ci = 5;
    boost::any a = ci;

    int i = boost::any_cast<int>(a);
    ASSERT_EQ(5, i);
}

TEST(GTestValue, Test3) {
    int i = 9;
    Value v = &i;

    int* ip;
    ASSERT_TRUE(to<int*>(v, &ip));
    ASSERT_EQ(&i, ip);

    const int* cip;
    ASSERT_FALSE(to<const int*>(v, &cip));
}

TEST(GTestAny, Test3) {
    int i = 9;
    boost::any a = &i;

    int* ip = boost::any_cast<int*>(a);
    ASSERT_EQ(&i, ip);

    ASSERT_ANY_THROW(boost::any_cast<const int*>(a));
}

TEST(GTestValue, Test4) {
    const int i = 11;
    Value v = &i;

    int* ip;
    ASSERT_FALSE(to<int*>(v, &ip));

    const int* cip;
    ASSERT_TRUE(to<const int*>(v, &cip));
    ASSERT_EQ(&i, cip);
}

TEST(GTestAny, Test4) {
    const int i = 11;
    boost::any a = &i;

    ASSERT_ANY_THROW(boost::any_cast<int*>(a));

    const int* cip = boost::any_cast<const int*>(a);
    ASSERT_EQ(&i, cip);
}

TEST(GTestValue, Test5) {
    Value v = 3;

    int i;
    int& ir = i;
    ASSERT_TRUE(to<int&>(v, &ir));
    ASSERT_EQ(3, ir);

    v = 5;
    ASSERT_TRUE(to<const int&>(v, &ir));
    ASSERT_EQ(5, ir);

    int64_t l;
    int64_t& lr = l;
    ASSERT_FALSE(to<int64_t&>(v, &lr));
}

TEST(GTestAny, Test5) {
    boost::any a = 3;

    int i;
    int& ir = i;
    ir = boost::any_cast<int&>(a);
    ASSERT_EQ(3, ir);

    a = 5;
    ir = boost::any_cast<const int&>(a);
    ASSERT_EQ(5, ir);

    int64_t l;
    int64_t& lr = l;
    ASSERT_ANY_THROW(lr = boost::any_cast<int64_t&>(a));
}

TEST(GTestValue, Test6) {
    const Value v = 3;

    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(3, i);

    ASSERT_TRUE(to<const int>(v, &i));
    ASSERT_EQ(3, i);

    int64_t l;
    ASSERT_FALSE(to<int64_t>(v, &l));
}

TEST(GTestAny, Test6) {
    const boost::any a = 3;

    int i = boost::any_cast<int>(a);
    ASSERT_EQ(3, i);

    i = boost::any_cast<const int>(a);
    ASSERT_EQ(3, i);

    ASSERT_ANY_THROW(boost::any_cast<int64_t>(a));
}

TEST(GTestValue, Test7) {
    const Value v = 3;
    int i;
    int& ir = i;
    ASSERT_TRUE(to<const int&>(v, &ir));
    ASSERT_EQ(3, ir);
}

TEST(GTestAny, Test7) {
    const boost::any a = 3;
    int i;
    int& ir = i;
    ir = boost::any_cast<const int&>(a);
    ASSERT_EQ(3, ir);
}

TEST(GTestValue, Test8) {
    Value v = 3;
    Value* vp = &v;

    int* ip;
    ASSERT_TRUE(to<int>(vp, &ip));
    ASSERT_EQ(3, *ip);

    int64_t* lp;
#if 1
    ASSERT_FALSE(to<int64_t>(vp, &lp));
#else
    ASSERT_TRUE(to<int64_t>(vp, &lp));
    ASSERT_EQ(3, *lp);
#endif
}

TEST(GTestAny, Test8) {
    boost::any a = 3;
    boost::any* ap = &a;

    int* ip  = boost::any_cast<int>(ap);
    ASSERT_EQ(3, *ip);

//  Segmentation fault
//  int64_t* lp = boost::any_cast<int64_t>(ap);
//  ASSERT_EQ(3, *lp);
}

TEST(GTestValue, Test9) {
    Value v = 3;
    const Value* vp = &v;

    const int* ip;
    ASSERT_TRUE(to<int>(vp, &ip));
    ASSERT_EQ(3, *ip);

    v = 5;
    ASSERT_TRUE(to<const int>(vp, &ip));
    ASSERT_EQ(5, *ip);
}

TEST(GTestAny, Test9) {
    boost::any a = 3;
    const boost::any* ap = &a;

    const int* ip = boost::any_cast<int>(ap);
    ASSERT_EQ(3, *ip);

    a = 5;
    ip = boost::any_cast<const int>(ap);
    ASSERT_EQ(5, *ip);
}

TEST(GTestValue, TestInstanceOf) {
    String::CPtr s = String::create("abc");
    Value v = s;
    ASSERT_TRUE(v.instanceof(Type<String>::id()));
    ASSERT_FALSE(v.instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(v.instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(v.instanceof(Type<Object>::id()));
    ASSERT_FALSE(v.instanceof(Type<int>::id()));

    v = 1;
    ASSERT_FALSE(v.instanceof(Type<Object>::id()));
    ASSERT_FALSE(v.instanceof(Type<int>::id()));
}

TEST(GTestValue, TestSingletonToPtrAndCPtr) {
    Null::Ptr null = Null::instance();
    Null::CPtr cnull = Null::instance();
    String::CPtr str = String::create("null");

    Value v = null;

    Null::Ptr n = toPtr<Null>(v);
    ASSERT_TRUE(n->toString()->equals(str));
    Null::CPtr cn = toCPtr<Null>(v);
    ASSERT_TRUE(cn->toString()->equals(str));
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_TRUE(co->toString()->equals(str));
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    Immutable::CPtr ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    Singleton::Ptr s = toPtr<Singleton>(v);
    ASSERT_TRUE(s->toString()->equals(str));
    Singleton::CPtr cs = toCPtr<Singleton>(v);
    ASSERT_TRUE(cs->toString()->equals(str));

    v = cnull;

    n = toPtr<Null>(v);
    ASSERT_FALSE(n);
    cn = toCPtr<Null>(v);
    ASSERT_TRUE(cn->toString()->equals(str));
    co = toCPtr<Object>(v);
    ASSERT_TRUE(co->toString()->equals(str));
    m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    s = toPtr<Singleton>(v);
    ASSERT_FALSE(s);
    cs = toCPtr<Singleton>(v);
    ASSERT_TRUE(cs->toString()->equals(str));
}

TEST(GTestValue, TestMutableToPtrAndCPtr) {
    ArrayList::Ptr arr = ArrayList::create();
    ArrayList::CPtr carr = arr;
    arr->add(1);
    arr->add(2);

    Value v = arr;

    ArrayList::Ptr a = toPtr<ArrayList>(v);
    ASSERT_EQ(2, a->size());
    ArrayList::CPtr ca = toCPtr<ArrayList>(v);
    ASSERT_EQ(2, ca->size());
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_EQ(Type<ArrayList>::id(), co->type());
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_EQ(Type<ArrayList>::id(), m->type());
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_EQ(Type<ArrayList>::id(), cm->type());
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
    ASSERT_EQ(Type<ArrayList>::id(), ca->type());
    co = toCPtr<Object>(v);
    ASSERT_EQ(Type<ArrayList>::id(), co->type());
    m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    cm = toCPtr<Mutable>(v);
    ASSERT_EQ(Type<ArrayList>::id(), cm->type());
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
    ASSERT_TRUE(x->equals(str));
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_TRUE(co->toString()->equals(str));
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    Immutable::CPtr ci = toCPtr<Immutable>(v);
    ASSERT_TRUE(ci->toString()->equals(str));
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

    ASSERT_GT(0, v1.compareTo(v2));
    ASSERT_LT(0, v2.compareTo(v1));
    ASSERT_EQ(0, v1.compareTo(v3));
    ASSERT_NE(0, v1.compareTo(v4));
}

TEST(GTestValue, TestCompareTo2) {
    ArrayList::Ptr p = ArrayList::create();
    ArrayList::CPtr cp = p;
    Value v = p;
    Value cv = cp;
    Value pv = 3;

    ASSERT_EQ(0, v.compareTo(v));
    ASSERT_EQ(0, v.compareTo(cv));
    ASSERT_NE(0, v.compareTo(pv));
    ASSERT_NE(0, v.compareTo(String::create()));
    ASSERT_NE(0, v.compareTo(ArrayList::create()));
    ASSERT_EQ(0, cv.compareTo(v));
    ASSERT_EQ(0, cv.compareTo(cv));
    ASSERT_NE(0, cv.compareTo(pv));
    ASSERT_NE(0, cv.compareTo(String::create()));
    ASSERT_NE(0, cv.compareTo(ArrayList::create()));
    ASSERT_NE(0, pv.compareTo(v));
    ASSERT_NE(0, pv.compareTo(cv));
    ASSERT_EQ(0, pv.compareTo(pv));
    ASSERT_EQ(0, pv.compareTo(3));
}

TEST(GTestValue, TestIsPtrAndIsCPtr) {
    ArrayList::Ptr p = ArrayList::create();
    ArrayList::CPtr cp = p;
    Value v = p;
    Value cv = cp;
    Value pv = 3;

    ASSERT_TRUE(v.isPtr());
    ASSERT_FALSE(v.isCPtr());
    ASSERT_FALSE(cv.isPtr());
    ASSERT_TRUE(cv.isCPtr());
    ASSERT_FALSE(pv.isPtr());
    ASSERT_FALSE(pv.isCPtr());
}

struct GTestValueStruct {};

TEST(GTestValue, TestType) {
    int i = 3;
    Value v1 = i;
    const Value v2 = v1;
    Value v3 = v2;
    ASSERT_EQ(Type<int>::id(), v3.type());

    GTestValueStruct x;
    GTestValueStruct* y;

    Value v4 = &x;
    const Value& v5 = v4;
    const Value v6 = v5;
    ASSERT_EQ(Type<GTestValueStruct*>::id(), v6.type());
    ASSERT_TRUE(to<GTestValueStruct*>(v6, &y));
    ASSERT_EQ(&x, y);
}

}  // namespace libj
