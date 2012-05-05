// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/mutable.h>
#include <libj/string.h>

namespace libj {

class GTestMutable : LIBJ_MUTABLE(GTestMutable)
};

class GTestMutableImpl : public GTestMutable {
 public:
    Type<GTestMutable>::Ptr clone() const {
        return GTestMutable::create();
    }

    Type<String>::Cptr toString() const {
        Type<String>::Cptr p;
        return p;
    }

    static int count;

    GTestMutableImpl() : GTestMutable() { count++; }
    ~GTestMutableImpl() { count--; }
};

int GTestMutableImpl::count = 0;

Type<GTestMutable>::Ptr GTestMutable::create() {
    Type<GTestMutable>::Ptr p(new GTestMutableImpl);
    return p;
}

#ifdef LIBJ_GTEST_BUILD_ERRORS
// #define LIBJ_GTEST_MUTABLE_BUILD_ERRORS
#endif

#ifdef LIBJ_GTEST_MUTABLE_BUILD_ERRORS
TEST(GTestMutalbe, Error) {
    Type<GTestMutable>::Ptr p = GTestMutable::create();
    Type<Immutable>::Cptr p2 = p;
}

TEST(GTestMutable, Error2) {
    new GTestMutable();
}

TEST(GTestMutable, Error3) {
    // noncopyable
    GTestMutableImpl x, y = x;
}

TEST(GTestMutable, Error4) {
    // noncopyable
    GTestMutableImpl x, y;
    x = y;
}
#endif

class GTestMutableX {
 public:
    virtual ~GTestMutableX() {}
    virtual int x() {}
};

TEST(GTestMutable, Test) {
    // check EBCO
    ASSERT_EQ(
        sizeof(GTestMutableImpl),
        sizeof(GCBase) + sizeof(GTestMutableX));
}

TEST(GTestMutable, Test2) {
    // no build errors
    Type<GTestMutable>::Ptr p = GTestMutable::create();
    Type<Mutable>::Ptr p2 = p;
    Type<Mutable>::Cptr p3 = p;
    Type<Object>::Ptr p4 = p;
    Type<Object>::Cptr p5 = p;
    Type<Mutable>::Ptr p6 = LIBJ_STATIC_PTR_CAST(Mutable)(p4);
    Type<Mutable>::Cptr p7 = LIBJ_STATIC_CPTR_CAST(Mutable)(p5);
    //Type<Mutable>::Ptr p8 = LIBJ_STATIC_CPTR_CAST(Mutable)(p4);
}

TEST(GTestMutable, Test3) {
    Type<GTestMutable>::Ptr p = GTestMutable::create();
    ASSERT_TRUE(p->instanceOf(Type<GTestMutable>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Mutable>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
TEST(GTestMutable, Test4) {
    {
        Type<GTestMutable>::Ptr p = GTestMutable::create();
        ASSERT_EQ(p.use_count(), 1);
        ASSERT_EQ(GTestMutableImpl::count, 1);

        Type<GTestMutable>::Ptr p2 = GTestMutable::create();
        ASSERT_EQ(p2.use_count(), 1);
        ASSERT_EQ(GTestMutableImpl::count, 2);

        p = p2;
        ASSERT_EQ(p.use_count(), 2);
        ASSERT_EQ(p2.use_count(), 2);
        ASSERT_EQ(GTestMutableImpl::count, 1);
    }
    ASSERT_EQ(GTestMutableImpl::count, 0);
}
#endif

}  // namespace libj
