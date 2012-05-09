// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/singleton.h>

namespace libj {

class GTestSingleton : LIBJ_SINGLETON(GTestSingleton)
};

class GTestSingletonX {
 public:
    virtual ~GTestSingletonX() {}
    virtual int x() {}
};

TEST(GTestSingleton, Test) {
    // check EBCO
    ASSERT_EQ(sizeof(GTestSingleton), sizeof(GTestSingletonX));
}

TEST(GTestSingleton, Test2) {
    // no build errors
    GTestSingleton::Ptr p = GTestSingleton::instance();
    Singleton::Ptr p2 = p;
    Singleton::CPtr p3 = p;
    Object::CPtr p5(p);
}

TEST(GTestSingleton, Test3) {
    GTestSingleton::Ptr p = GTestSingleton::instance();
    ASSERT_TRUE(p->instanceOf(Type<GTestSingleton>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Singleton>::id()));
    ASSERT_TRUE(p->instanceOf(Type<Object>::id()));
}

#ifdef LIBJ_USE_SP
class GTestSingleton2 : public SingletonTmpl<GTestSingleton2> {
 public:
    TypeId type() const {
        return Type<GTestSingleton2>::id();
    }

    static int count;

 private:
    friend class SingletonTmpl<GTestSingleton2>;
    GTestSingleton2() : SingletonTmpl<GTestSingleton2>() { count++; }
    ~GTestSingleton2() { count--; }
};

int GTestSingleton2::count = 0;

TEST(GTestSingleton, Test4) {
    {
        GTestSingleton2::Ptr p = GTestSingleton2::instance();
        ASSERT_EQ(p.use_count(), 1);
        ASSERT_EQ(GTestSingleton2::count, 1);

        GTestSingleton2::Ptr p2 = GTestSingleton2::instance();
        ASSERT_EQ(p.use_count(), 1);
        ASSERT_EQ(GTestSingleton2::count, 1);

        p = p2;
        ASSERT_EQ(p.use_count(), 2);
        ASSERT_EQ(p2.use_count(), 2);
        ASSERT_EQ(GTestSingleton2::count, 1);
    }
    ASSERT_EQ(GTestSingleton2::count, 1);
}
#endif

}  // namespace libj
