// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <boost/any.hpp>
#include <libj/array_list.h>
#include <libj/singleton.h>
#include <libj/string.h>
#include <libj/value.h>

#ifdef LIBJ_USE_MSVC
namespace std {
    template <>
    struct hash<const int> {
        std::size_t operator()(const int& key) const {
            return hash<int>()(static_cast<int>(key));
        }
    };
}
#endif

namespace libj {

TEST(GTestValue, TestIsUndefined) {
    Value v;
    ASSERT_TRUE(v.isUndefined());
    v = 0;
    ASSERT_FALSE(v.isUndefined());

    ASSERT_TRUE(UNDEFINED.isUndefined());
}

TEST(GTestValue, TestIsNull) {
    Value v = Object::null();
    ASSERT_TRUE(v.isNull());

    v = String::null();
    ASSERT_TRUE(v.isNull());

    v = String::create();
    ASSERT_FALSE(v.isNull());

    v = ArrayList::null();
    ASSERT_TRUE(v.isNull());

    v = ArrayList::create();
    ASSERT_FALSE(v.isNull());

    v = 0;
    ASSERT_FALSE(v.isNull());

    // same as 'v = 0'
    // v = NULL;
    // ASSERT_FALSE(v.isNull());

    v = 5;
    ASSERT_FALSE(v.isNull());
}

TEST(GTestValue, TestIsPrimitive) {
    Value v;
    ASSERT_FALSE(v.isPrimitive());

    v = 7;
    ASSERT_TRUE(v.isPrimitive());

    v = String::null();
    ASSERT_FALSE(v.isPrimitive());

    v = String::create();
    ASSERT_FALSE(v.isPrimitive());
}

TEST(GTestValue, TestIsObject) {
    Value v;
    ASSERT_FALSE(v.isObject());

    v = 7;
    ASSERT_FALSE(v.isObject());

    v = String::null();
    ASSERT_FALSE(v.isObject());

    v = String::create();
    ASSERT_TRUE(v.isObject());
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

    Value null = String::null();

    ASSERT_TRUE(null.isPtr());
    ASSERT_TRUE(null.isCPtr());
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
    ASSERT_TRUE(detail::_to<int>(vp, &ip, false));
    ASSERT_EQ(3, *ip);

    v = 5;
    const int* cip;
    ASSERT_TRUE(detail::_to<int>(vp, &cip));
    ASSERT_EQ(5, *cip);

    // differ from boost::any!
    ASSERT_FALSE(detail::_to<const int>(vp, &cip, false));

    int64_t* lp;
    ASSERT_FALSE(detail::_to<int64_t>(vp, &lp, false));
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
    ASSERT_TRUE(detail::_to<int>(vp, &cip));
    ASSERT_EQ(3, *cip);

    v = 5;
    ASSERT_TRUE(detail::_to<const int>(vp, &cip));
    ASSERT_EQ(5, *cip);

    const int64_t* clp;
    ASSERT_FALSE(detail::_to<int64_t>(vp, &clp));
    ASSERT_FALSE(detail::_to<const int64_t>(vp, &clp));
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
    ASSERT_TRUE(!s);

    Immutable::CPtr i;
    ASSERT_TRUE(to<Immutable::CPtr>(v, &i));
    ASSERT_TRUE(!i);

    Mutable::Ptr m = ArrayList::create();
    ASSERT_TRUE(to<Mutable::Ptr>(v, &m));
    ASSERT_TRUE(!m);

    Double d;
    ASSERT_FALSE(to<Double>(v, &d));

    v = Immutable::null();
    s = String::create("123");
    ASSERT_TRUE(to<String::CPtr>(v, &s));
    ASSERT_TRUE(!s);
}

TEST(GTestValue, TestTo12) {
    Value v = 5;
    int i = to<int>(v);
    ASSERT_EQ(5, i);

    i = to<int>(v, 3);
    ASSERT_EQ(5, i);

    double d = to<double>(v);
    ASSERT_EQ(0.0, d);

    d = to<double>(v, 3.3);
    ASSERT_EQ(3.3, d);
}

TEST(GTestValue, TestInstanceOf) {
    String::CPtr s = String::create("abc");
    Value v = s;
    ASSERT_TRUE(v.instanceof(Type<String>::id()));
    ASSERT_FALSE(v.instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(v.instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(v.instanceof(Type<Object>::id()));
    ASSERT_FALSE(v.instanceof(Type<int>::id()));

    Value n = String::null();
    ASSERT_FALSE(n.instanceof(Type<String>::id()));
    ASSERT_FALSE(n.instanceof(Type<Object>::id()));

    v = 1;
    ASSERT_FALSE(v.instanceof(Type<Object>::id()));
    ASSERT_FALSE(v.instanceof(Type<int>::id()));
}

class GTestValueSingleton : LIBJ_SINGLETON(GTestValueSingleton)
 public:
    String::CPtr toString() const {
        return String::create("GTestValueSingleton");
    }
};

TEST(GTestValue, TestSingletonToPtrAndCPtr) {
    GTestValueSingleton::Ptr singleton = GTestValueSingleton::instance();
    GTestValueSingleton::CPtr csingleton = singleton;

    Value v = singleton;

    GTestValueSingleton::Ptr g = toPtr<GTestValueSingleton>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), g->type());
    GTestValueSingleton::CPtr cg = toCPtr<GTestValueSingleton>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), cg->type());
    GTestValueSingleton::CPtr cg2 = toPtr<GTestValueSingleton>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), cg2->type());
    Object::CPtr co = toCPtr<Object>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), co->type());
    Mutable::Ptr m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    Mutable::CPtr cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    Immutable::CPtr ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    Singleton::Ptr s = toPtr<Singleton>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), s->type());
    Singleton::CPtr cs = toCPtr<Singleton>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), cs->type());

    v = csingleton;

    g = toPtr<GTestValueSingleton>(v);
    ASSERT_FALSE(g);
    cg = toCPtr<GTestValueSingleton>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), cg->type());
    cg2 = toPtr<GTestValueSingleton>(v);
    ASSERT_FALSE(cg2);
    co = toCPtr<Object>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), co->type());
    m = toPtr<Mutable>(v);
    ASSERT_FALSE(m);
    cm = toCPtr<Mutable>(v);
    ASSERT_FALSE(cm);
    ci = toCPtr<Immutable>(v);
    ASSERT_FALSE(ci);
    s = toPtr<Singleton>(v);
    ASSERT_FALSE(s);
    cs = toCPtr<Singleton>(v);
    ASSERT_EQ(Type<GTestValueSingleton>::id(), cs->type());
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
    Value undef;
    Value intv = 123;
    Value snull = String::null();
    Value anull = ArrayList::null();
    Value empty = String::create();
    Value abcde = String::create("abcde");

    ASSERT_EQ(0, snull.compareTo(snull));
    ASSERT_EQ(0, snull.compareTo(anull));
    ASSERT_GT(0, snull.compareTo(empty));
    ASSERT_GT(0, snull.compareTo(abcde));
    ASSERT_LT(0, snull.compareTo(undef));

    ASSERT_EQ(0, anull.compareTo(snull));
    ASSERT_EQ(0, anull.compareTo(anull));
    ASSERT_GT(0, anull.compareTo(empty));
    ASSERT_GT(0, anull.compareTo(abcde));
    ASSERT_LT(0, anull.compareTo(undef));

    ASSERT_LT(0, empty.compareTo(snull));
    ASSERT_LT(0, empty.compareTo(anull));
    ASSERT_EQ(0, empty.compareTo(empty));
    ASSERT_GT(0, empty.compareTo(abcde));
    ASSERT_LT(0, empty.compareTo(undef));

    ASSERT_LT(0, abcde.compareTo(snull));
    ASSERT_LT(0, abcde.compareTo(anull));
    ASSERT_LT(0, abcde.compareTo(empty));
    ASSERT_EQ(0, abcde.compareTo(abcde));
    ASSERT_LT(0, abcde.compareTo(undef));

    ASSERT_GT(0, undef.compareTo(snull));
    ASSERT_GT(0, undef.compareTo(anull));
    ASSERT_GT(0, undef.compareTo(empty));
    ASSERT_GT(0, undef.compareTo(abcde));
    ASSERT_EQ(0, undef.compareTo(undef));
    ASSERT_GT(0, undef.compareTo(intv));

    ASSERT_GT(0, snull.compareTo(intv) * intv.compareTo(snull));
    ASSERT_GT(0, anull.compareTo(intv) * intv.compareTo(anull));
    ASSERT_GT(0, empty.compareTo(intv) * intv.compareTo(empty));
    ASSERT_GT(0, abcde.compareTo(intv) * intv.compareTo(abcde));
}

TEST(GTestValue, TestEquals) {
    Value f = false;
    ASSERT_TRUE(f.equals(false));
    ASSERT_FALSE(f.equals(true));

    Value x = 1.23;
    ASSERT_TRUE(x.equals(1.23));
    ASSERT_FALSE(x.equals(4.56));

    Value g = GTestValueSingleton::instance();
    ASSERT_TRUE(g.equals(GTestValueSingleton::instance()));
    ASSERT_FALSE(g.equals(String::create()));

    Value v;
    ASSERT_TRUE(v.equals(UNDEFINED));
}

TEST(GTestValue, TestOperators) {
    Value x = 1;
    Value y = 2;
    ASSERT_TRUE(x < y);
    ASSERT_TRUE(y > x);
    ASSERT_TRUE(x <= y);
    ASSERT_TRUE(y >= x);
    ASSERT_TRUE(x != y);
    ASSERT_FALSE(x > y);
    ASSERT_FALSE(y < x);
    ASSERT_FALSE(x >= y);
    ASSERT_FALSE(y <= x);
    ASSERT_FALSE(x == y);

    x = 1.5;
    y = 1.5;
    ASSERT_TRUE(x == y);
    ASSERT_TRUE(y == x);
    ASSERT_TRUE(x <= y);
    ASSERT_TRUE(y <= x);
    ASSERT_TRUE(x >= y);
    ASSERT_TRUE(y >= x);
    ASSERT_FALSE(x < y);
    ASSERT_FALSE(y < x);
    ASSERT_FALSE(x > y);
    ASSERT_FALSE(y > x);
    ASSERT_FALSE(x != y);
    ASSERT_FALSE(y != x);

    ASSERT_TRUE(x <= 1.5);
    ASSERT_TRUE(x == 1.5);
    ASSERT_TRUE(x >= 1.5);
    ASSERT_FALSE(x < 1.5);
    ASSERT_FALSE(x > 1.5);
    ASSERT_FALSE(x != 1.5);
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

    Value str = String::create("abc");
    ASSERT_EQ(Type<String::CPtr>::id(), str.type());

    Value null = String::null();
    ASSERT_EQ(1, null.type());

    Value v;
    ASSERT_EQ(0, v.type());
    ASSERT_EQ(0, UNDEFINED.type());
}

TEST(GTestValue, TestIs) {
    int i = 2;
    Value v1 = i;
    ASSERT_TRUE(v1.is<int>());
    ASSERT_FALSE(v1.is<double>());

    Value str = String::create("abc");
    ASSERT_TRUE(str.is<Object>());
    ASSERT_TRUE(str.is<String>());
    ASSERT_FALSE(str.is<ArrayList>());

    Value null = String::null();
    ASSERT_FALSE(null.is<String>());
}

}  // namespace libj
