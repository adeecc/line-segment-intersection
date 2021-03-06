#pragma once

#include <comparable_segment.hpp>
#include <line_segment.hpp>
#include <point.hpp>
#include <vector>

using point_t = Geometry::Point;
using segment_t = Geometry::LineSegment;

struct Event {
   private:
   public:
    point_t* pt;

    std::vector<ComparableSegment*> lower;
    std::vector<ComparableSegment*> upper;
    std::vector<ComparableSegment*> contain;

    Event(point_t* pt, ComparableSegment* seg, int type) : pt(pt) {
        // TODO: Verify this THOROUGHLY
        switch (type) {
            case 0:
                lower.push_back(seg);
                break;
            case 1:
                upper.push_back(seg);
                break;
            case 2:
                contain.push_back(seg);
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
};