// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/mutable.h>
#include <libj/immutable.h>
#include <libj/string.h>
#include <libj/detail/gc_delete.h>
#include <libj/detail/gc_collect.h>

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

TEST(GTestImmutable, TestIs) {
    GTestImmutable::CPtr p = GTestImmutable::create();

    ASSERT_TRUE(p->is<GTestImmutable>());
    ASSERT_TRUE(p->is<Immutable>());
    ASSERT_TRUE(p->is<Object>());

    ASSERT_FALSE(p->is<Mutable>());
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

        GTestImmutable::CPtr p3 =
            LIBJ_STATIC_CPTR_CAST(GTestImmutable)((&(*p))->self());
        ASSERT_EQ(3, p.use_count());
        ASSERT_EQ(3, p2.use_count());
        ASSERT_EQ(3, p3.use_count());
        ASSERT_EQ(1, GTestImmutable::count);
    }
    ASSERT_EQ(0, GTestImmutable::count);
}

#else

TEST(GTestImmutable, TestGcDelete) {
    LIBJ_GC_COLLECT;
    int cnt = GTestImmutable::count;

    GTestImmutable::CPtr p = GTestImmutable::create();
    ASSERT_EQ(cnt + 1, GTestImmutable::count);

    LIBJ_GC_DELETE(p);
    ASSERT_EQ(cnt, GTestImmutable::count);
}

#endif

}  // namespace libj
