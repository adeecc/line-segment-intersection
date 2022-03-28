/**
 * @file event.hpp
 * @brief Declaration of the Event Datastructure, storing the event point, p, and the sets L(p), U(p) and C(p)
 */
#pragma once

#include <comparable_segment.hpp>
#include <line_segment.hpp>
#include <point.hpp>
#include <vector>

/// Type Alias for Point
using point_t = Geometry::Point;
/// Type Alias for Line Segment
using segment_t = Geometry::LineSegment;

struct Event {
    /// Categorises the types of event points
    enum class Type : uint8_t {
        UPPER,    ///< The event point, p is the upper point of a segment
        LOWER,    ///< The event point, p is the lower point of a segment
        CONTAIN,  ///< The event point, p is within a segment, more specifically at an intersection point
        OTHER     ///< Dummy event point created. The point p might not lie on any segment
    };

    /// Initializing variable of Type point_t
    point_t pt;
    /// Initializing vector of segments with the current point as their lower point; The set L(p)
    std::vector<ComparableSegment> lower;
    /// Initializing vector of segments with the current point as their upper point; The set U(p)
    std::vector<ComparableSegment> upper;
    /// Initializing vector of segments with the current point as their interior point; The set C(p)
    std::vector<ComparableSegment> contain;

    /**
     * @brief Construct a new Event object
     *
     */
    Event() = default;

    /**
     * @brief Construct a new Event object, and push the segment into to corresponding set: L, U or C
     *
     * @param pt
     * @param seg
     * @param type
     */
    Event(const point_t& pt, const ComparableSegment& seg, Type type) : pt(pt) {
        switch (type) {
            case Type::UPPER:
                upper.push_back(seg);
                break;
            case Type::LOWER:
                lower.push_back(seg);
                break;
            case Type::CONTAIN:
                contain.push_back(seg);
                break;
            case Type::OTHER:
                break;
            default:
                assert(0);
                break;
        }
    }

    /**
     * @brief Overloading the operator| (Union Operation between two events)
     *
     * @param lhs
     * @param rhs
     * @return Event
     */
    friend Event operator|(const Event& lhs, const Event& rhs) {
        Event res{lhs};

        res.lower.insert(res.lower.end(), rhs.lower.begin(), rhs.lower.end());
        res.upper.insert(res.upper.end(), rhs.upper.begin(), rhs.upper.end());
        res.contain.insert(res.contain.end(), rhs.contain.begin(), rhs.contain.end());

        return res;
    }

    /**
     * @brief Overloading the operator<=>
     * @return -1 if Left Point < Right Point
     * @return 0 if Left Point = Right Point
     * @return 1 if Left Point > RIGHT Point
     */
    friend int operator<=>(const Event& lhs, const Event& rhs) {
        if (lhs.pt < rhs.pt)
            return -1;
        else if (lhs.pt == rhs.pt)
            return 0;
        else
            return 1;
    }

    /**
     * @brief Overloading the operator==
     *
     * @param lhs
     * @param rhs
     * @return false if Left Point not equals Right Point
     * @return true if Left Point = Right Point
     */
    friend bool operator==(const Event& lhs, const Event& rhs) {
        return (lhs.pt == rhs.pt);
    }
};