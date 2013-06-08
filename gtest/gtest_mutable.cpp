// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/mutable.h>
#include <libj/immutable.h>
#include <libj/cast.h>
#include <libj/string.h>
#include <libj/detail/gc_delete.h>
#include <libj/detail/gc_collect.h>

namespace libj {

class GTestMutable : LIBJ_MUTABLE(GTestMutable)
 public:
    static Ptr create();

    static int count;
    GTestMutable() { count++; }
    ~GTestMutable() { count--; }

    String::CPtr toString() const {
        return String::create();
    }
};

int GTestMutable::count = 0;

GTestMutable::Ptr GTestMutable::create() {
    return Ptr(new GTestMutable);
}

class GTestMutableX {
 public:
    virtual ~GTestMutableX() {}
    virtual int x() { return 0; }
};

#ifndef LIBJ_PF_WINDOWS

TEST(GTestMutable, TestEBCO) {
    ASSERT_EQ(
        sizeof(detail::GCBase) + sizeof(GTestMutableX),
        sizeof(GTestMutable));
}

#endif

TEST(GTestMutable, TestSubstitution) {
    GTestMutable::Ptr p = GTestMutable::create();
    Mutable::Ptr p2 = p;
    Mutable::CPtr p3 = p;
    Object::CPtr p4 = p;
    Mutable::CPtr p5 = LIBJ_STATIC_CPTR_CAST(Mutable)(p4);
    GTestMutable::Ptr p6 = LIBJ_STATIC_PTR_CAST(GTestMutable)(p2);
    ASSERT_TRUE(p && p2 && p3 && p4 && p5 && p6);
}


TEST(GTestMutable, TestNull) {
    GTestMutable::Ptr p = GTestMutable::null();
    Mutable::CPtr p2 = Mutable::null();
    ASSERT_FALSE(p || p2);
}

TEST(GTestMutable, TestInstanceOf) {
    GTestMutable::Ptr p = GTestMutable::create();

    ASSERT_TRUE(p->instanceof(Type<GTestMutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));

    ASSERT_FALSE(p->instanceof(Type<Immutable>::id()));
}

TEST(GTestMutable, TestInstanceOf2) {
    GTestMutable::CPtr p = GTestMutable::create();

    ASSERT_TRUE(p->instanceof(Type<GTestMutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));

    ASSERT_FALSE(p->instanceof(Type<Immutable>::id()));
}

#ifdef LIBJ_USE_SP

TEST(GTestMutable, TestUseCount) {
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

        GTestMutable::Ptr p3 =
            LIBJ_STATIC_PTR_CAST(GTestMutable)((&(*p))->self());
        ASSERT_EQ(3, p.use_count());
        ASSERT_EQ(3, p2.use_count());
        ASSERT_EQ(3, p3.use_count());
        ASSERT_EQ(1, GTestMutable::count);
    }
    ASSERT_EQ(0, GTestMutable::count);
}

#else

TEST(GTestMutable, TestGcCollectAndDelete) {
    LIBJ_GC_COLLECT;
    ASSERT_EQ(0, GTestMutable::count);

    GTestMutable::Ptr p = GTestMutable::create();
    ASSERT_EQ(1, GTestMutable::count);

    LIBJ_GC_DELETE(p);
    ASSERT_EQ(0, GTestMutable::count);
}

#endif

}  // namespace libj
