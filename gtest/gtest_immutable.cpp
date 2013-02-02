// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/immutable.h>
#include <libj/mutable.h>
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
    return CPtr(new GTestImmutable);
}

class GTestImmutableX {
 public:
    virtual ~GTestImmutableX() {}
    virtual int x() { return 0; }
};

#ifndef LIBJ_PF_WINDOWS

TEST(GTestImmutable, TestEBCO) {
    ASSERT_EQ(
        sizeof(detail::GCBase) + sizeof(GTestImmutableX),
        sizeof(GTestImmutable));
}

#endif

TEST(GTestImmutable, TestSubstitution) {
    GTestImmutable::CPtr p = GTestImmutable::create();
    Immutable::CPtr p2 = p;
    Object::CPtr p3 = p;
    ASSERT_TRUE(p && p2 && p3);
}

TEST(GTestImmutable, TestNull) {
    GTestImmutable::CPtr p = GTestImmutable::null();
    Immutable::CPtr p2 = Immutable::null();
    ASSERT_FALSE(p || p2);
}

TEST(GTestImmutable, TestInstanceOf) {
    GTestImmutable::CPtr p = GTestImmutable::create();

    ASSERT_TRUE(p->instanceof(Type<GTestImmutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Immutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));

    ASSERT_FALSE(p->instanceof(Type<Mutable>::id()));
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
