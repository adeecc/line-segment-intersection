#include <gtest/gtest.h>

#include <limits>
#include <point.hpp>

TEST(PointTest, DefaultConstructor) {
    Geometry::Point pt;
    ASSERT_EQ(pt.x, std::numeric_limits<int>::min());
    ASSERT_EQ(pt.y, std::numeric_limits<int>::min());
}

TEST(PointTest, ParameterizedConstructor) {
    Geometry::Point pt(3.14, 4.20);
    ASSERT_EQ(pt.x, 3.14);
    ASSERT_EQ(pt.y, 4.20);
}

TEST(PointTest, LargeDeltaComparisonOperatorTest) {
    const double EPS = 1;
    const double x = 3, y = 2;

    Geometry::Point a(x, y), b(x + 2 * EPS, y), c(x, y + 2 * EPS), d(x + 2 * EPS, y + 2 * EPS);

    // c    d
    // a    b

    ASSERT_LT(c, d);
    ASSERT_LT(c, a);
    ASSERT_LT(a, b);
    ASSERT_LT(c, b);
    ASSERT_LT(d, a);
    ASSERT_LT(d, b);
}

TEST(PointTest, SmallDeltaComparisonOperatorTest) {
    const double EPS = 1e-9;
    const double x = 3, y = 2;

    Geometry::Point a(x, y), b(x + 2 * EPS, y), c(x, y + 2 * EPS), d(x + 2 * EPS, y + 2 * EPS);

    // c    d
    // a    b

    ASSERT_LT(c, d);
    ASSERT_LT(c, a);
    ASSERT_LT(a, b);
    ASSERT_LT(c, b);
    ASSERT_LT(d, a);
    ASSERT_LT(d, b);
}