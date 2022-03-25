#pragma once

#include <line_segment.hpp>
#include <point.hpp>
#include <rb_tree.hpp>

// oEUv

using point_t = Geometry::Point;
using segment_t = Geometry::LineSegment;

struct ComparableSegment : public segment_t {
    double* sweep_line_y = nullptr;

    ComparableSegment() : segment_t() {}

    ComparableSegment(const segment_t& seg, double* sweep_line_y)
        : segment_t(seg), sweep_line_y(sweep_line_y) {}

    ComparableSegment(point_t _u, point_t _v, double* sweep_line_y)
        : segment_t(_u, _v), sweep_line_y(sweep_line_y) {}

    friend auto operator<=>(const ComparableSegment& lhs, const ComparableSegment& rhs) {
        assert(lhs.sweep_line_y == rhs.sweep_line_y);

        auto lhs_intersection = ComparableSegment::compute_intersection(lhs, *lhs.sweep_line_y);
        auto rhs_intersection = ComparableSegment::compute_intersection(rhs, *rhs.sweep_line_y);

        if (lhs_intersection.x < rhs_intersection.x)
            return -1;
        else if (lhs_intersection.x == rhs_intersection.x)
            return 0;
        else
            return 1;
    }

    friend bool operator==(const ComparableSegment& lhs, const ComparableSegment& rhs) {
        if (lhs.sweep_line_y != rhs.sweep_line_y) {
            assert(lhs.sweep_line_y == rhs.sweep_line_y);
        }

        auto lhs_intersection = ComparableSegment::compute_intersection(lhs, *lhs.sweep_line_y);
        auto rhs_intersection = ComparableSegment::compute_intersection(rhs, *rhs.sweep_line_y);

        return lhs_intersection.x == rhs_intersection.x;
    }
};
