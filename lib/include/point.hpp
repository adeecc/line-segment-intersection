/**
 * @file point.hpp
 * @brief Point Implementation
 */
#pragma once

#include <limits>
#include <ostream>

/// Namespace with all geometrical constructs
namespace Geometry {

/**
 * @brief A struct for defining a point
 *
 */
struct Point {
    /// The epsilon value to be used for all comparisons
    static constexpr double EPS = std::numeric_limits<float>::epsilon();

    /// x coordinate of the point
    double x;

    /// y coordinate of the point
    double y;

    /**
     * @brief  Default Construct a point
     *
     */
    constexpr Point() : x(std::numeric_limits<int>::min()), y(std::numeric_limits<int>::min()) {}

    /**
     * @brief Construct a new Point object with the specified coordinates
     *
     * @param x
     * @param y
     */
    Point(double x, double y) : x(x), y(y) {}

    /**
     * @brief Overload the operator<=>
     * Defines a strict ordering on all points
     * @param lhs
     * @param rhs
     */
    friend int operator<=>(const Point& lhs, const Point& rhs) {
        if ((lhs.y > rhs.y) or (lhs.y == rhs.y and lhs.x < rhs.x))
            return -1;
        else if (lhs.x == rhs.x and lhs.y == rhs.y)
            return 0;
        else
            return 1;
    }

    /**
     * @brief overload operator==
     *
     * @param lhs
     * @param rhs
     * @return true
     * @return false
     */
    friend bool operator==(const Point& lhs, const Point& rhs) {
        return std::abs(lhs.x - rhs.x) < Point::EPS and
               std::abs(lhs.y - rhs.y) < Point::EPS;
    }

    /**
     * @brief Overloading the operator<<
     *
     * @param stream Output Stream to be written on
     * @param pt point to write
     * @return std::ostream& reference to the updated output stream
     */
    friend std::ostream& operator<<(std::ostream& stream, const Point& pt) {
        stream << "(" << pt.x << ", " << pt.y << ")";
        return stream;
    }
};
}  // namespace Geometry
