#pragma once

#include <comparable_segment.hpp>
#include <line_segment.hpp>
#include <point.hpp>
#include <vector>

using point_t = Geometry::Point;
using segment_t = Geometry::LineSegment;

struct Event {
    enum class Type : uint8_t {
        UPPER,
        LOWER,
        CONTAIN,
        OTHER
    };

    point_t pt;

    std::vector<ComparableSegment> lower;
    std::vector<ComparableSegment> upper;
    std::vector<ComparableSegment> contain;

    Event() = default;
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

    friend Event operator|(const Event& lhs, const Event& rhs) {
        Event res{lhs};

        res.lower.insert(res.lower.end(), rhs.lower.begin(), rhs.lower.end());
        res.upper.insert(res.upper.end(), rhs.upper.begin(), rhs.upper.end());
        res.contain.insert(res.contain.end(), rhs.contain.begin(), rhs.contain.end());

        return res;
    }

    friend auto operator<=>(const Event& lhs, const Event& rhs) {
        if (lhs.pt < rhs.pt)
            return -1;
        else if (lhs.pt == rhs.pt)
            return 0;
        else
            return 1;
    }

    friend auto operator==(const Event& lhs, const Event& rhs) {
        return (lhs.pt == rhs.pt);
    }
};