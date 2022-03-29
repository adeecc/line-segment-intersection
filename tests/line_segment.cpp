#include <gtest/gtest.h>

#include <limits>
#include <line_segment.hpp>

TEST(LineSegmentTest, DefaultConstructor) {
    Geometry::LineSegment seg;
    ASSERT_EQ(seg.u.x, std::numeric_limits<int>::min());
    ASSERT_EQ(seg.u.y, std::numeric_limits<int>::min());
    ASSERT_EQ(seg.v.x, std::numeric_limits<int>::min());
    ASSERT_EQ(seg.v.y, std::numeric_limits<int>::min());
}

TEST(LineSegmentTest, ParameterizedConstructors) {
    Geometry::LineSegment seg(Geometry::Point(2, 3), Geometry::Point(4, 5));
    ASSERT_EQ(seg.u.x, 2);
    ASSERT_EQ(seg.u.y, 3);
    ASSERT_EQ(seg.v.x, 4);
    ASSERT_EQ(seg.v.y, 5);

    seg = Geometry::LineSegment(2, 3, 4, 5);
    ASSERT_EQ(seg.u.x, 2);
    ASSERT_EQ(seg.u.y, 3);
    ASSERT_EQ(seg.v.x, 4);
    ASSERT_EQ(seg.v.y, 5);
}

TEST(LineSegmentTest, ArraySubscriptOperator) {
    Geometry::LineSegment seg(2, 3, 4, 5);

    ASSERT_EQ(seg[0].x, 4);
    ASSERT_EQ(seg[0].y, 5);
    ASSERT_EQ(seg[1].x, 2);
    ASSERT_EQ(seg[1].y, 3);

    // seg[0] = Geometry::Point(10, 11);
    // ASSERT_EQ(seg[0].x, 10);
    // ASSERT_EQ(seg[0].y, 11);

    // seg[1] = Geometry::Point(12, 13);
    // ASSERT_EQ(seg[1].x, 12);
    // ASSERT_EQ(seg[1].y, 13);
}

TEST(LineSegmentTest, IntersectionWithHorizonalLine) {
    // TODO: Add test that checks proper edge cases, and corner points
}