/**
 * @file line_segment.hpp
 * @brief Line Segment Implementation
 */
#pragma once

#include <assert.h>

#include <limits>
#include <ostream>
#include <point.hpp>
#include <utility>

/// Namespace with all geometrical constructs
namespace Geometry {

/**
 * @brief Struct describing a line segment objecs defined by two end points
 */
struct LineSegment {
    static constexpr double EPS = std::numeric_limits<float>::epsilon();

    /// Variable representing one (of two) end point of a Line Segment
    Point u;

    /// Variable representing one (of two) end point of a Line Segment
    Point v;

    /**
     * @brief Construct a new Line Segment object
     *
     */
    LineSegment() = default;

    /**
     * @brief Construct a new Line Segment object with end points
     *
     */
    LineSegment(Point _u, Point _v) : u(_u), v(_v) {}

    /**
     * @brief Construct a new Line Segment object with endpoint coordinates
     *
     */
    LineSegment(double ux, double uy, double vx, double vy) : u(ux, uy), v(vx, vy) {}

    /**
     * @brief This method is for obtaining the top point of the segment
     *
     * @return Point& - reference to top point of a segment
     */
    Point& top() { return (u < v) ? u : v; }

    /**
     * @brief This method is for obtaining the top point of the segment
     *
     * @return const Point& - const reference to top point of a segment
     */
    [[nodiscard]] const Point& top() const { return (u < v) ? u : v; }

    /**
     * @brief This method is for obtaining the bottom point of the segment
     *
     * @return Point& - reference to bottom point of a segment
     */
    Point& bottom() { return (u < v) ? v : u; }

    /**
     * @brief This method is for obtaining the bottom point of the segment
     *
     * @return const Point& - const reference to bottom point of a segment
     */
    [[nodiscard]] const Point& bottom() const { return (u < v) ? v : u; }

    /**
     * @brief Overloading the operator[]
     *
     * @param idx
     * @return Point& returns top point when index 0 is enterd, bottom point otherwise
     */
    Point& operator[](std::size_t idx) { return idx ? bottom() : top(); }

    /**
     * @brief Overloading the operator[]
     *
     * @param idx
     * @return const Point& returns top point when index 0 is enterd, bottom point otherwise
     */
    const Point& operator[](std::size_t idx) const { return idx ? bottom() : top(); }

    /**
     * @brief Overloading the operator<<
     *
     * @param stream Output Stream to be written on
     * @param l line segment to write
     * @return std::ostream& reference to the updated output stream
     */
    friend std::ostream& operator<<(std::ostream& stream, const LineSegment& l) {
        stream << "[" << l.top() << "->" << l.bottom() << "]";
        return stream;
    }

    /**
     * @brief Determine if two line segments intersect internally
     *
     * @param l1 first line segment
     * @param l2 second line segment
     * @return true if the line segments intersect
     * @return false if the line segments do not intersect
     */
    static bool does_intersect(const LineSegment& l1, const LineSegment& l2);

    /**
     * @brief Determine the internal intersection point of two line segments. If the given line segments do not intersect internally then the behaviour is undefined.
     *
     * @param l1 first line segment
     * @param l2 second line segment
     * @return Point of intersection
     */
    static Point compute_intersection(const LineSegment& l1, const LineSegment& l2);

    /**
     * @brief Determine where a given line segment intersects with the given horizontal line
     *
     * @param l1 first line segment
     * @param y horizontal line
     * @return Point of intersection
     */
    static Point compute_intersection(const LineSegment& l1, double y);

    /**
     * @brief Determine where a line segment (given by its endpoints) intersects with the given horizontal line
     *
     * @param l1 first line segment
     * @param y horizontal line
     * @return Point of intersection
     */
    static Point compute_intersection(const Point& u, const Point& v, double y);
};
}  // namespace Geometry
