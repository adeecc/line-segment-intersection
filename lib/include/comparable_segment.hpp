/**
 * @file comparable_segment.hpp
 * @brief Defining Strict Ordering on Line Segments 
 */
#pragma once

#include <line_segment.hpp>
#include <point.hpp>
#include <rb_tree.hpp>

/// Type Alias for Point
using point_t = Geometry::Point;
/// Type Alias for Line Segment
using segment_t = Geometry::LineSegment;

/**
 * @brief This struct inherits from segment_t and defines comparisions on them
 * 
 */
struct ComparableSegment : public segment_t {
    double* sweep_line_y = nullptr;

    /**
     * @brief Construct a new Comparable Segment object
     * 
     */
    ComparableSegment() : segment_t() {}

    /**
     * @brief Construct a new Comparable Segment object
     * 
     * @param seg 
     * @param sweep_line_y 
     */
    ComparableSegment(const segment_t& seg, double* sweep_line_y)
        : segment_t(seg), sweep_line_y(sweep_line_y) {}
    /**
     * @brief Construct a new Comparable Segment object
     * 
     * @param _u 
     * @param _v 
     * @param sweep_line_y 
     */
    ComparableSegment(point_t _u, point_t _v, double* sweep_line_y)
        : segment_t(_u, _v), sweep_line_y(sweep_line_y) {}

    /** 
     * @brief Defining the operator <=> on line segments
     * @param lhs 
     * @param rhs
     */

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

    /**
     * @brief defining '==' operator overload
     * 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */

    friend bool operator==(const ComparableSegment& lhs, const ComparableSegment& rhs) {
        if (lhs.sweep_line_y != rhs.sweep_line_y) {
            assert(lhs.sweep_line_y == rhs.sweep_line_y);
        }

        auto lhs_intersection = ComparableSegment::compute_intersection(lhs, *lhs.sweep_line_y);
        auto rhs_intersection = ComparableSegment::compute_intersection(rhs, *rhs.sweep_line_y);

        return lhs_intersection.x == rhs_intersection.x;
    }
};
