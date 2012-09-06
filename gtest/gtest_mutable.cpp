// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/mutable.h>
#include <libj/string.h>

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
    GTestMutable::Ptr p(new GTestMutable);
    return p;
}

class GTestMutableX {
 public:
    virtual ~GTestMutableX() {}
    virtual int x() { return 0; }
};

TEST(GTestMutable, TestEBCO) {
    ASSERT_EQ(
        sizeof(GTestMutable),
        sizeof(GCBase) + sizeof(GTestMutableX));
}

TEST(GTestMutable, TestSubstitution) {
    GTestMutable::Ptr p = GTestMutable::create();
    Mutable::Ptr p2 = p;
    Mutable::CPtr p3 = p;
    Object::CPtr p4 = p;
    Mutable::CPtr p5 = LIBJ_STATIC_CPTR_CAST(Mutable)(p4);
    GTestMutable::Ptr p6 = LIBJ_STATIC_PTR_CAST(GTestMutable)(p2);
    ASSERT_TRUE(p && p2 && p3 && p4 && p5 && p6);
}

TEST(GTestMutable, TestInstanceOf) {
    GTestMutable::Ptr p = GTestMutable::create();
    ASSERT_TRUE(p->instanceof(Type<GTestMutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Mutable>::id()));
    ASSERT_TRUE(p->instanceof(Type<Object>::id()));
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
    }
    ASSERT_EQ(0, GTestMutable::count);
}
#endif

}  // namespace libj
