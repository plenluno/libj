// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/immutable.h>
#include <libj/string.h>

namespace libj {

class GTestImmutable : LIBJ_IMMUTABLE(GTestImmutable)
 public:
    String::CPtr toString() const {
        String::CPtr p(String::create());
        return p;
    }

    static int count;
    static CPtr create();

 private:
    GTestImmutable() { count++; }

 public:
    ~GTestImmutable() { count--; }
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

TEST(GTestImmutable, Test) {
    // check EBCO
    ASSERT_EQ(
        sizeof(GTestImmutable),
        sizeof(GCBase) + sizeof(GTestImmutableX));
}

TEST(GTestImmutable, Test2) {
    // no build errors
    GTestImmutable::CPtr p = GTestImmutable::create();
    Immutable::CPtr p2 = p;
    Object::CPtr p3 = p;
}

TEST(GTestImmutable, Test3) {
    GTestImmutable::CPtr p = GTestImmutable::create();
    ASSERT_TRUE(p->instanceOf(Type<GTestImmutable>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Immutable>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
TEST(GTestImmutable, Test4) {
    {
        GTestImmutable::CPtr p = GTestImmutable::create();
        ASSERT_EQ(p.use_count(), 1);
        ASSERT_EQ(GTestImmutable::count, 1);

        GTestImmutable::CPtr p2 = GTestImmutable::create();
        ASSERT_EQ(p2.use_count(), 1);
        ASSERT_EQ(GTestImmutable::count, 2);

        p = p2;
        ASSERT_EQ(p.use_count(), 2);
        ASSERT_EQ(p2.use_count(), 2);
        ASSERT_EQ(GTestImmutable::count, 1);
    }
    ASSERT_EQ(GTestImmutable::count, 0);
}
#endif

}  // namespace libj

