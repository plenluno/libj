// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/mutable.h>
#include <libj/string.h>

namespace libj {

class GTestMutable : LIBJ_MUTABLE(GTestMutable)
 public:
    String::CPtr toString() const {
        String::CPtr p(String::create());
        return p;
    }

    static int count;
    static Ptr create();

 private:
    GTestMutable() { count++; }

 public:
    ~GTestMutable() { count--; }
};

int GTestMutable::count = 0;

GTestMutable::Ptr GTestMutable::create() {
    GTestMutable::Ptr p(new GTestMutable);
    return p;
}

#ifdef LIBJ_GTEST_BUILD_ERRORS
// #define LIBJ_GTEST_MUTABLE_BUILD_ERRORS
#endif

#ifdef LIBJ_GTEST_MUTABLE_BUILD_ERRORS
TEST(GTestMutalbe, Error) {
    GTestMutable::Ptr p = GTestMutable::create();
    Immutable::CPtr p2 = p;
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
    virtual int x() { return 0; }
};

TEST(GTestMutable, Test) {
    // check EBCO
    ASSERT_EQ(
        sizeof(GTestMutable),
        sizeof(GCBase) + sizeof(GTestMutableX));
}

TEST(GTestMutable, Test2) {
    // no build errors
    GTestMutable::Ptr p = GTestMutable::create();
    Mutable::Ptr p2 = p;
    Mutable::CPtr p3 = p;
    Object::CPtr p4 = p;
    Mutable::CPtr p5 = LIBJ_STATIC_CPTR_CAST(Mutable)(p4);
    GTestMutable::Ptr p6 = LIBJ_STATIC_PTR_CAST(GTestMutable)(p2);
    ASSERT_TRUE(p && p2 && p3 && p4 && p5 && p6);
}

TEST(GTestMutable, Test3) {
    GTestMutable::Ptr p = GTestMutable::create();
    ASSERT_TRUE(p->instanceof(Type<GTestMutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
TEST(GTestMutable, Test4) {
    {
        GTestMutable::Ptr p = GTestMutable::create();
        ASSERT_EQ(1, p.use_count());
        ASSERT_EQ(1, GTestMutable::count);

        GTestMutable::Ptr p2 = GTestMutable::create();
        ASSERT_EQ(1, p2.use_count());
        ASSERT_EQ(2, GTestMutable::count);

        p = p2;
        ASSERT_EQ(2, p.use_count());
        ASSERT_EQ(2, p2.use_count());
        ASSERT_EQ(1, GTestMutable::count);
    }
    ASSERT_EQ(0, GTestMutable::count);
}
#endif

}  // namespace libj
