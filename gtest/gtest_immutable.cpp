// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/immutable.h>
#include <libj/string.h>

namespace libj {

class GTestImmutable : LIBJ_IMMUTABLE(GTestImmutable)
 public:
    static CPtr create();

    static int count;
    GTestImmutable() { count++; }
    ~GTestImmutable() { count--; }

    String::CPtr toString() const {
        return String::create();
    }
};

int GTestImmutable::count = 0;

GTestImmutable::CPtr GTestImmutable::create() {
    GTestImmutable::CPtr p(new GTestImmutable);
    return p;
}

#ifdef LIBJ_GTEST_BUILD_ERRORS
// #define LIBJ_GTEST_IMMUTABLE_BUILD_ERRORS
#endif

#ifdef LIBJ_GTEST_IMMUTABLE_BUILD_ERRORS
TEST(GTestImmutalbe, Error) {
    GTestImmutable::Ptr p;
}

TEST(GTestImmutable, Error2) {
    GTestImmutable::CPtr p = GTestImmutable::create();
    Mutable::CPtr p2 = p;
}

TEST(GTestImmutable, Error3) {
    // noncopyable
    GTestImmutableImpl x, y = x;
}

TEST(GTestMutable, Error4) {
    // noncopyable
    GTestImmutableImpl x, y;
    x = y;
}
#endif

class GTestImmutableX {
 public:
    virtual ~GTestImmutableX() {}
    virtual int x() { return 0; }
};

TEST(GTestImmutable, TestEBCO) {
    ASSERT_EQ(
        sizeof(GTestImmutable),
        sizeof(GCBase) + sizeof(GTestImmutableX));
}

TEST(GTestImmutable, TestSubstitution) {
    GTestImmutable::CPtr p = GTestImmutable::create();
    Immutable::CPtr p2 = p;
    Object::CPtr p3 = p;
    ASSERT_TRUE(p && p2 && p3);
}

TEST(GTestImmutable, TestInstanceOf) {
    GTestImmutable::CPtr p = GTestImmutable::create();
    ASSERT_TRUE(p->instanceof(Type<GTestImmutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
TEST(GTestImmutable, TestUseCount) {
    {
        GTestImmutable::CPtr p = GTestImmutable::create();
        ASSERT_EQ(1, p.use_count());
        ASSERT_EQ(1, GTestImmutable::count);

        GTestImmutable::CPtr p2 = GTestImmutable::create();
        ASSERT_EQ(1, p2.use_count());
        ASSERT_EQ(2, GTestImmutable::count);

        p = p2;
        ASSERT_EQ(2, p.use_count());
        ASSERT_EQ(2, p2.use_count());
        ASSERT_EQ(1, GTestImmutable::count);
    }
    ASSERT_EQ(0, GTestImmutable::count);
}
#endif

}  // namespace libj

