// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/math.h>
#include <libj/console.h>
#include <libj/constant.h>

namespace libj {

TEST(GTestMath, TestIsNaN) {
    ASSERT_TRUE(isNaN(QUIET_NAN));
    ASSERT_TRUE(isNaN(SIGNALING_NAN));
    ASSERT_FALSE(isNaN(1.0));
}

TEST(GTestMath, TestIsFinite) {
    ASSERT_TRUE(isFinite(1.0));
    ASSERT_FALSE(isFinite(QUIET_NAN));
    ASSERT_FALSE(isFinite(SIGNALING_NAN));
    ASSERT_FALSE(isFinite(POSITIVE_INFINITY));
    ASSERT_FALSE(isFinite(NEGATIVE_INFINITY));
}

TEST(GTestMath, TestIsInfinite) {
    ASSERT_TRUE(isInfinite(POSITIVE_INFINITY));
    ASSERT_TRUE(isInfinite(NEGATIVE_INFINITY));
    ASSERT_FALSE(isInfinite(1.0));
}

TEST(GTestMath, TestRandom) {
    Double r1 = math::random();
    Double r2 = math::random();
    Double r3 = math::random();
    ASSERT_NE(r1, r2);
    ASSERT_NE(r2, r3);
    ASSERT_NE(r3, r1);
    ASSERT_TRUE(r1 >= 0.0 && r1 < 1.0);
    ASSERT_TRUE(r2 >= 0.0 && r2 < 1.0);
    ASSERT_TRUE(r3 >= 0.0 && r3 < 1.0);
}

TEST(GTestMath, TestPow) {
    ASSERT_EQ(4.0, math::pow(2.0, 2.0));

    ASSERT_EQ(1.0, math::pow(QUIET_NAN, 0.0));
    ASSERT_EQ(1.0, math::pow(POSITIVE_INFINITY, 0.0));
    ASSERT_EQ(1.0, math::pow(NEGATIVE_INFINITY, 0.0));

    ASSERT_TRUE(isNaN(math::pow(1.0, QUIET_NAN)));
    ASSERT_TRUE(isNaN(math::pow(1.0, POSITIVE_INFINITY)));
    ASSERT_TRUE(isNaN(math::pow(1.0, NEGATIVE_INFINITY)));
}

TEST(GTestMath, TestMax) {
    ASSERT_EQ(2.0, math::max(1.0, 2.0));
    ASSERT_EQ(2.0, math::max(2.0, 1.0));
    ASSERT_EQ(POSITIVE_INFINITY, math::max(1.0, POSITIVE_INFINITY));

    ASSERT_TRUE(isNaN(math::max(QUIET_NAN, 1.0)));
    ASSERT_TRUE(isNaN(math::max(1.0, SIGNALING_NAN)));
}

TEST(GTestMath, TestMin) {
    ASSERT_EQ(1.0, math::min(1.0, 2.0));
    ASSERT_EQ(1.0, math::min(2.0, 1.0));
    ASSERT_EQ(NEGATIVE_INFINITY, math::min(1.0, NEGATIVE_INFINITY));

    ASSERT_TRUE(isNaN(math::min(QUIET_NAN, 1.0)));
    ASSERT_TRUE(isNaN(math::min(1.0, SIGNALING_NAN)));
}

}  // namespace libj
