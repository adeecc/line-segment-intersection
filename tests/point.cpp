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
    double del = 1;
    double x = 3, y = 2;

    Geometry::Point a(x, y), b(x + 2 * del, y), c(x, y + 2 * del), d(x + 2 * del, y + 2 * del);

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
    double del = Geometry::Point::EPS;
    double x = 3, y = 2;

    Geometry::Point a(x, y), b(x + 2 * del, y), c(x, y + 2 * del), d(x + 2 * del, y + 2 * del);

    // c    d
    // a    b

    ASSERT_LT(c, d);
    ASSERT_LT(c, a);
    ASSERT_LT(a, b);
    ASSERT_LT(c, b);
    ASSERT_LT(d, a);
    ASSERT_LT(d, b);
}