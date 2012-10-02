// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <boost/any.hpp>
#include <libj/array_list.h>
#include <libj/string.h>
#include <libj/undefined.h>
#include <libj/value.h>

namespace libj {

TEST(GTestValue, TestIsEmpty) {
    Value v;
    ASSERT_TRUE(v.isEmpty());
    v = 0;
    ASSERT_FALSE(v.isEmpty());

    ASSERT_TRUE(NO_VALUE.isEmpty());
}

TEST(GTestValue, TestTo1) {
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

TEST(GTestAny, TestCast1) {
    boost::any a = 3;
    int i = boost::any_cast<int>(a);
    ASSERT_EQ(3, i);

    a = 5;
    i = boost::any_cast<const int>(a);
    ASSERT_EQ(5, i);

    ASSERT_ANY_THROW(boost::any_cast<int64_t>(a));
}

TEST(GTestValue, TestTo2) {
    const Value v = 3;

    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(3, i);

    ASSERT_TRUE(to<const int>(v, &i));
    ASSERT_EQ(3, i);

    int64_t l;
    ASSERT_FALSE(to<int64_t>(v, &l));
}

TEST(GTestAny, TestCast2) {
    const boost::any a = 3;

    int i = boost::any_cast<int>(a);
    ASSERT_EQ(3, i);

    i = boost::any_cast<const int>(a);
    ASSERT_EQ(3, i);

    ASSERT_ANY_THROW(boost::any_cast<int64_t>(a));
}

TEST(GTestValue, TestTo3) {
    const int ci = 5;
    Value v = ci;

    int i;
    ASSERT_TRUE(to<int>(v, &i));
    ASSERT_EQ(5, i);
}

TEST(GTestAny, TestCast3) {
    const int ci = 5;
    boost::any a = ci;

    int i = boost::any_cast<int>(a);
    ASSERT_EQ(5, i);
}

TEST(GTestValue, TestTo4) {
    int i = 9;
    Value v = &i;

    int* ip;
    ASSERT_TRUE(to<int*>(v, &ip));
    ASSERT_EQ(&i, ip);
    ASSERT_EQ(9, *ip);

    const int* cip;
    ASSERT_FALSE(to<const int*>(v, &cip));
}

TEST(GTestAny, TestCast4) {
    int i = 9;
    boost::any a = &i;

    int* ip = boost::any_cast<int*>(a);
    ASSERT_EQ(&i, ip);
    ASSERT_EQ(9, *ip);

    ASSERT_ANY_THROW(boost::any_cast<const int*>(a));
}

TEST(GTestValue, TestTo5) {
    const int i = 11;
    Value v = &i;

    int* ip;
    ASSERT_FALSE(to<int*>(v, &ip));

    const int* cip;
    ASSERT_TRUE(to<const int*>(v, &cip));
    ASSERT_EQ(&i, cip);
    ASSERT_EQ(11, *cip);
}

TEST(GTestAny, TestCast5) {
    const int i = 11;
    boost::any a = &i;

    ASSERT_ANY_THROW(boost::any_cast<int*>(a));

    const int* cip = boost::any_cast<const int*>(a);
    ASSERT_EQ(&i, cip);
    ASSERT_EQ(11, *cip);
}

TEST(GTestValue, TestTo6) {
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
    ASSERT_FALSE(to<const int64_t&>(v, &lr));
}

TEST(GTestAny, TestCast6) {
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
    ASSERT_ANY_THROW(lr = boost::any_cast<const int64_t&>(a));
}

TEST(GTestValue, TestTo7) {
    const Value v = 3;

    int i;
    int& ir = i;
    ASSERT_TRUE(to<int&>(v, &ir));
    ASSERT_EQ(3, ir);

    ASSERT_TRUE(to<const int&>(v, &ir));
    ASSERT_EQ(3, ir);

    int64_t l;
    int64_t& lr = l;
    ASSERT_FALSE(to<int64_t&>(v, &lr));
    ASSERT_FALSE(to<const int64_t&>(v, &lr));
}

TEST(GTestAny, TestCast7) {
    const boost::any a = 3;

    int i;
    int& ir = i;
    // build error
    // ir = boost::any_cast<int&>(a);
    // ASSERT_EQ(3, ir);

    ir = boost::any_cast<const int&>(a);
    ASSERT_EQ(3, ir);

    int64_t l;
    int64_t& lr = l;
    // build error
    // ASSERT_ANY_THROW(lr = boost::any_cast<int64_t&>(a));
    ASSERT_ANY_THROW(lr = boost::any_cast<const int64_t&>(a));
}

TEST(GTestValue, TestTo8) {
    Value v = 3;
    Value* vp = &v;

    int* ip;
    ASSERT_TRUE(to<int>(vp, &ip));
    ASSERT_EQ(3, *ip);

    v = 5;
    const int* cip;
    ASSERT_TRUE(to<int>(vp, &cip));
    ASSERT_EQ(5, *cip);

    // differ from boost::any!
    ASSERT_FALSE(to<const int>(vp, &cip));

    int64_t* lp;
    ASSERT_FALSE(to<int64_t>(vp, &lp));
}

TEST(GTestAny, TestCast8) {
    boost::any a = 3;
    boost::any* ap = &a;

    int* ip  = boost::any_cast<int>(ap);
    ASSERT_EQ(3, *ip);

    a = 5;
    const int* cip = boost::any_cast<int>(ap);
    ASSERT_EQ(5, *cip);

    a = 7;
    cip = boost::any_cast<const int>(ap);
    ASSERT_EQ(7, *cip);

    // Segmentation fault
    // int64_t* lp = boost::any_cast<int64_t>(ap);
    // ASSERT_EQ(7, *lp);
}

TEST(GTestValue, TestTo9) {
    Value v = 3;
    const Value* vp = &v;

    const int* cip;
    ASSERT_TRUE(to<int>(vp, &cip));
    ASSERT_EQ(3, *cip);

    v = 5;
    ASSERT_TRUE(to<const int>(vp, &cip));
    ASSERT_EQ(5, *cip);

    const int64_t* clp;
    ASSERT_FALSE(to<int64_t>(vp, &clp));
    ASSERT_FALSE(to<const int64_t>(vp, &clp));
}

TEST(GTestAny, TestCast9) {
    boost::any a = 3;
    const boost::any* ap = &a;

    const int* cip = boost::any_cast<int>(ap);
    ASSERT_EQ(3, *cip);

    a = 5;
    cip = boost::any_cast<const int>(ap);
    ASSERT_EQ(5, *cip);

    // Segmentation fault
    // const int64_t* clp = boost::any_cast<int64_t>(ap);
    // ASSERT_EQ(5, *clp);
    // const int64_t* clp2 = boost::any_cast<const int64_t>(ap);
    // ASSERT_EQ(5, *clp2);
}

TEST(GTestValue, TestTo10) {
    Value v = String::create("abc");
    String::CPtr s;
    ASSERT_TRUE(to<String::CPtr>(v, &s));
    ASSERT_TRUE(s->equals(String::create("abc")));

    Immutable::CPtr i1;
    ASSERT_FALSE(to<Immutable::CPtr>(v, &i1));

    Immutable::CPtr i2 = String::create("123");
    v = i2;
    Immutable::CPtr i3;
    ASSERT_TRUE(to<Immutable::CPtr>(v, &i3));
    ASSERT_TRUE(i3->equals(String::create("123")));
}

TEST(GTestValue, TestTo11) {
    Value v = String::null();
    String::CPtr s = String::create("abc");
    ASSERT_TRUE(to<String::CPtr>(v, &s));
    ASSERT_FALSE(s);

    Immutable::CPtr i1;
    ASSERT_FALSE(to<Immutable::CPtr>(v, &i1));

    Immutable::CPtr i2 = String::null();
    v = i2;
    Immutable::CPtr i3 = String::create("123");
    ASSERT_TRUE(to<Immutable::CPtr>(v, &i3));
    ASSERT_FALSE(i3);
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
    Undefined::Ptr undef = Undefined::instance();
    Undefined::CPtr cundef = Undefined::instance();

    Value v = undef;

    Undefined::Ptr u = toPtr<Undefined>(v);
    ASSERT_EQ(Type<Undefined>::id(), u->type());
    Undefined::CPtr cu = toCPtr<Undefined>(v);
    ASSERT_EQ(Type<Undefined>::id(), cu->type());
    Undefined::CPtr cu2 = toPtr<Undefined>(v);
    ASSERT_EQ(Type<Undefined>::id(), cu2->type());
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_EQ(Type<Undefined>::id(), co->type());
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    Immutable::CPtr ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    Singleton::Ptr s = toPtr<Singleton>(v);
    ASSERT_EQ(Type<Undefined>::id(), s->type());
    Singleton::CPtr cs = toCPtr<Singleton>(v);
    ASSERT_EQ(Type<Undefined>::id(), cs->type());

    v = cundef;

    u = toPtr<Undefined>(v);
    ASSERT_FALSE(u);
    cu = toCPtr<Undefined>(v);
    ASSERT_EQ(Type<Undefined>::id(), cu->type());
    cu2 = toPtr<Undefined>(v);
    ASSERT_FALSE(cu2);
    co = toCPtr<Object>(v);
    ASSERT_EQ(Type<Undefined>::id(), co->type());
    m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    s = toPtr<Singleton>(v);
    ASSERT_FALSE(s);
    cs = toCPtr<Singleton>(v);
    ASSERT_EQ(Type<Undefined>::id(), cs->type());
}

TEST(GTestValue, TestMutableToPtrAndCPtr) {
    ArrayList::Ptr arr = ArrayList::create();
    ArrayList::CPtr carr = arr;
    arr->add(1);
    arr->add(2);

    Value v = arr;

    ArrayList::Ptr a = toPtr<ArrayList>(v);
    ASSERT_EQ(Type<ArrayList>::id(), a->type());
    ArrayList::CPtr ca = toCPtr<ArrayList>(v);
    ASSERT_EQ(Type<ArrayList>::id(), ca->type());
    ArrayList::CPtr ca2 = toPtr<ArrayList>(v);
    ASSERT_EQ(Type<ArrayList>::id(), ca2->type());
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
    ca2 = toPtr<ArrayList>(v);
    ASSERT_FALSE(ca2);
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

TEST(GTestValue, TestNullToPtrAndCPtr) {
    String::CPtr null = String::null();

    String::CPtr x = toCPtr<String>(null);
    ASSERT_FALSE(x);
    Object::CPtr co = toCPtr<Object>(null);
    ASSERT_FALSE(co);
    Mutable::Ptr m = toPtr<Mutable>(null);
    ASSERT_FALSE(m);
    Mutable::CPtr cm = toCPtr<Mutable>(null);
    ASSERT_FALSE(cm);
    Immutable::CPtr ci = toCPtr<Immutable>(null);
    ASSERT_FALSE(ci);
    Singleton::Ptr s = toPtr<Singleton>(null);
    ASSERT_FALSE(s);
    Singleton::CPtr cs = toCPtr<Singleton>(null);
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
    ASSERT_GT(0, v1.compareTo(v4) * v4.compareTo(v1));
}

TEST(GTestValue, TestCompareTo2) {
    ArrayList::Ptr p = ArrayList::create();
    ArrayList::CPtr cp = p;
    Value v = p;
    Value cv = cp;
    Value pv = 3;
    Value sv = String::create();

    ASSERT_EQ(0, v.compareTo(v));
    ASSERT_EQ(0, v.compareTo(cv));

    ASSERT_EQ(0, cv.compareTo(v));
    ASSERT_EQ(0, cv.compareTo(cv));

    ASSERT_EQ(0, pv.compareTo(pv));
    ASSERT_EQ(0, pv.compareTo(3));

    ASSERT_GT(0, v.compareTo(pv) * pv.compareTo(v));
    ASSERT_GT(0, v.compareTo(sv) * sv.compareTo(v));
    ASSERT_GT(0, cv.compareTo(pv) * pv.compareTo(cv));
    ASSERT_GT(0, cv.compareTo(sv) * sv.compareTo(cv));
    ASSERT_GT(0, pv.compareTo(sv) * sv.compareTo(pv));
}

TEST(GTestValue, TestCompareTo3) {
    Value snull = String::null();
    Value anull = ArrayList::null();
    Value empty = String::create();
    Value abc = String::create("abc");
    Value intv = 123;

    ASSERT_EQ(0, snull.compareTo(snull));
    ASSERT_EQ(0, snull.compareTo(anull));
    ASSERT_GT(0, snull.compareTo(empty));
    ASSERT_GT(0, snull.compareTo(abc));

    ASSERT_EQ(0, anull.compareTo(snull));
    ASSERT_EQ(0, anull.compareTo(anull));
    ASSERT_GT(0, anull.compareTo(empty));
    ASSERT_GT(0, anull.compareTo(abc));

    ASSERT_LT(0, empty.compareTo(snull));
    ASSERT_LT(0, empty.compareTo(anull));
    ASSERT_EQ(0, empty.compareTo(empty));
    ASSERT_GT(0, empty.compareTo(abc));

    ASSERT_LT(0, abc.compareTo(snull));
    ASSERT_LT(0, abc.compareTo(anull));
    ASSERT_LT(0, abc.compareTo(empty));
    ASSERT_EQ(0, abc.compareTo(abc));

    ASSERT_GT(0, snull.compareTo(intv) * intv.compareTo(snull));
    ASSERT_GT(0, anull.compareTo(intv) * intv.compareTo(anull));
}

TEST(GTestValue, TestEquals) {
    Value f = false;
    ASSERT_TRUE(f.equals(false));
    ASSERT_FALSE(f.equals(true));

    Value x = 1.23;
    ASSERT_TRUE(x.equals(1.23));
    ASSERT_FALSE(x.equals(4.56));

    Value u = Undefined::instance();
    ASSERT_TRUE(u.equals(Undefined::instance()));
    ASSERT_FALSE(u.equals(String::create()));
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

TEST(GTestValue, TestType2) {
    Value obj = Object::null();
    ASSERT_EQ(Type<Object::CPtr>::id(), obj.type());

    Value str = String::create("abc");
    ASSERT_EQ(Type<String::CPtr>::id(), str.type());
}

}  // namespace libj
