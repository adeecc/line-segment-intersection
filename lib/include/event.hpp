/**
 * @file event.hpp
 * @brief Event Implementation
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
    /// An enum which denotes the Type of the Event
    enum class Type : uint8_t {
        UPPER,  ///< Denotes the starting point of a segment
        LOWER,  ///< Denotes the ending point of a segment
        CONTAIN,    ///< Denotes the interior point of a segment
        OTHER   ///<  Denotes if the point does not lie on the segment
    };

    /// Initializing variable of Type point_t
    point_t pt;
    /// Initializing vector of segments with the current point as ending point
    std::vector<ComparableSegment> lower;
    /// Initializing vector of segments with the current point as starting point
    std::vector<ComparableSegment> upper;
    /// Initializing vector of segments with the current point as interior point
    std::vector<ComparableSegment> contain;

    /**
     * @brief Construct a new Event object
     * 
     */
    Event() {}
    /**
     * @brief Construct a new Event object
     * 
     * @param pt 
     * @param seg 
     * @param type 
     */
    Event(const point_t& pt, const ComparableSegment& seg, Type type) : pt(pt) {
        // TODO: Verify this THOROUGHLY
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
     * @brief Overloading the operator | (Union Operation)
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
     * @brief Overloading the operator <=>
     * @return -1 if Left Point < Right Point
     * @return 0 if Left Point = Right Point
     * @return 1 if Left Point > RIGHT Point
     */
    

    friend auto operator<=>(const Event& lhs, const Event& rhs) {
        if (lhs.pt < rhs.pt)
            return -1;
        else if (lhs.pt == rhs.pt)
            return 0;
        else
            return 1;
    }

    /**
     * @brief Overloading the operator ==
     * 
     * @param lhs 
     * @param rhs 
     * @return 0 if Left Point not equals Right Point
     * @return 1 if Left Point = Right Point
     */
    friend auto operator==(const Event& lhs, const Event& rhs) {
        return (lhs.pt == rhs.pt);
    }
};