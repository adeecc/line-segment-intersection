/**
 * @file point.hpp
 * @brief Point Implementation
 */
#pragma once

#include <limits>
#include <ostream>

namespace Geometry {
/**
 * @brief A struct for defining a point
 * 
 */
struct Point {
    /// X - coordinate
    double x;
    /// Y - coordinate
    double y;

    /**
     * @brief  Constructor
     * 
     */

    constexpr Point() : x(std::numeric_limits<int>::min()), y(std::numeric_limits<int>::min()) {}
    /**
     * @brief Construct a new Point object
     * 
     * @param x 
     * @param y 
     */
    Point(double x, double y) : x(x), y(y) {}

    /** 
     * @brief Defining the operator <=> on points
     * @param lhs 
     * @param rhs
     */
    friend auto operator<=>(const Point& lhs, const Point& rhs) {
        if ((lhs.y > rhs.y) or (lhs.y == rhs.y and lhs.x < rhs.x))
            return -1;
        else if (lhs.x == rhs.x and lhs.y == rhs.y)
            return 0;
        else
            return 1;
    }

     /**
     * @brief defining '==' operator overload on points
     * 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    friend bool operator==(const Point& lhs, const Point& rhs) {
        return lhs.x == rhs.x and lhs.y == rhs.y;
    }

    /**
     * @brief Overloading the Left Shift operator << 
     * 
     * @param stream Output Stream to be written on
     * @param l line segment to write
     * @return std::ostream& reference to the output stream
     */
    
    friend std::ostream& operator<<(std::ostream& stream, const Point& pt) {
        stream << "(" << pt.x << ", " << pt.y << ")";
        return stream;
    }
};
}  // namespace Geometry
