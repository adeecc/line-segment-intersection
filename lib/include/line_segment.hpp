/**
 * @file line_segment.hpp
 * @brief Line Segment Implementation
 */
#pragma once

#include <assert.h>

#include <ostream>
#include <point.hpp>
#include <utility>

namespace Geometry {

struct LineSegment {
    /// Initializing a variable of Struct Point
    Point u;
    /// Initializing a variable of Struct Point
    Point v;

    /**
     * @brief Construct a new Line Segment object
     * 
     */
    LineSegment() = default;

    LineSegment(Point _u, Point _v) : u(_u), v(_v) {}
    LineSegment(double ux, double uy, double vx, double vy) : u(ux, uy), v(vx, vy) {}

    /**
     * @brief This method is for obtaining the top point of the segment
     * 
     * @return Point& - top point of a segment
     */
    Point& top() { return (u < v) ? u : v; }
    const Point& top() const { return (u < v) ? u : v; }

    /**
     * @brief This method is for obtaining the bottom point of the segment
     * 
     * @return Point& - bottom point of a segment
     */
    Point& bottom() { return (u < v) ? v : u; }
    const Point& bottom() const { return (u < v) ? v : u; }

    /**
     * @brief Overloading the operator []
     * 
     * @param idx 
     * @return Point& based on parameters, bottom point or top point is returned 
     */
    
    Point& operator[](std::size_t idx) { return idx ? bottom() : top(); }
    const Point& operator[](std::size_t idx) const { return idx ? bottom() : top(); }

    /**
     * @brief Overloading the Left Shift operator << 
     * 
     * @param stream Output Stream to be written on
     * @param l line segment to write
     * @return std::ostream& reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& stream, const LineSegment& l) {
        stream << "[" << l.top() << "->" << l.bottom() << "]";
        return stream;
    }

    /**
     * @brief For knowing if two line segments intersect
     * 
     * @param l1 first line segment 
     * @param l2 second line segment
     * @return true if the line segments intersect
     * @return false if the line segments do not intersect
     */
    static bool does_intersect(const LineSegment& l1, const LineSegment& l2);
    
    static Point compute_intersection(const LineSegment& l1, const LineSegment& l2);
    static Point compute_intersection(const Point& u, const Point& v, double y);
    static Point compute_intersection(const LineSegment& l1, double y);
};
}  // namespace Geometry
