// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/immutable.h>
#include <libj/string.h>

namespace libj {

class GTestImmutable : LIBJ_IMMUTABLE(GTestImmutable)
};

class GTestImmutableImpl : public GTestImmutable {
 public:
    Type<String>::Cptr toString() const {
        Type<String>::Cptr p;
        return p;
    }

    static int count;

    GTestImmutableImpl() : GTestImmutable() { count++; }
    ~GTestImmutableImpl() { count--; }
};

int GTestImmutableImpl::count = 0;

Type<GTestImmutable>::Cptr GTestImmutable::create() {
    Type<GTestImmutable>::Cptr p(new GTestImmutableImpl);
    return p;
}

#ifdef LIBJ_GTEST_BUILD_ERRORS
// #define LIBJ_GTEST_IMMUTABLE_BUILD_ERRORS
#endif

#ifdef LIBJ_GTEST_IMMUTABLE_BUILD_ERRORS
TEST(GTestImmutalbe, Error) {
    Type<GTestImmutable>::Ptr p;
}

TEST(GTestImmutable, Error2) {
    Type<GTestImmutable>::Cptr p = GTestImmutable::create();
    Type<Object>::Ptr p2 = p;
}

TEST(GTestImmutable, Error3) {
    Type<GTestImmutable>::Cptr p = GTestImmutable::create();
    Type<Mutable>::Cptr p2 = p;
}

TEST(GTestImmutable, Error4) {
    // noncopyable
    GTestImmutableImpl x, y = x;
}

TEST(GTestMutable, Error5) {
    // noncopyable
    GTestMutableImpl x, y;
    x = y;
}
#endif

class GTestImmutableX {
 public:
    virtual ~GTestImmutableX() {}
    virtual int x() {}
};

TEST(GTestImmutable, Test) {
    // check EBCO
    ASSERT_EQ(
        sizeof(GTestImmutableImpl),
        sizeof(GCBase) + sizeof(GTestImmutableX));
}

TEST(GTestImmutable, Test2) {
    // no build errors
    Type<GTestImmutable>::Cptr p = GTestImmutable::create();
    Type<Immutable>::Cptr p2 = p;
    Type<Object>::Cptr p3 = p;
}

TEST(GTestImmutable, Test3) {
    Type<GTestImmutable>::Cptr p = GTestImmutable::create();
    ASSERT_TRUE(p->instanceOf(Type<GTestImmutable>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Immutable>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
TEST(GTestImmutable, Test4) {
    {
        Type<GTestImmutable>::Cptr p = GTestImmutable::create();
        ASSERT_EQ(p.use_count(), 1);
        ASSERT_EQ(GTestImmutableImpl::count, 1);

        Type<GTestImmutable>::Cptr p2 = GTestImmutable::create();
        ASSERT_EQ(p2.use_count(), 1);
        ASSERT_EQ(GTestImmutableImpl::count, 2);

        p = p2;
        ASSERT_EQ(p.use_count(), 2);
        ASSERT_EQ(p2.use_count(), 2);
        ASSERT_EQ(GTestImmutableImpl::count, 1);
    }
    ASSERT_EQ(GTestImmutableImpl::count, 0);
}
#endif

}  // namespace libj

