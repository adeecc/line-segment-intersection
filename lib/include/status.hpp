#pragma once

#include <comparable_segment.hpp>
#include <rb_tree.hpp>

using point_t = Geometry::Point;
using segment_t = Geometry::LineSegment;

struct Status {
    using container_t = DS::rb_tree::tree_t<ComparableSegment, ComparableSegment*>;

    void insert(ComparableSegment* seg) {
        _container.insert(*seg, seg);
    }

    void erase(const ComparableSegment& seg) {
        _container.erase(seg);
    }

    ComparableSegment* lower_bound(const ComparableSegment& seg) {
        return _container.lower_bound(seg)->val;
    }

    ComparableSegment* upper_bound(const ComparableSegment& seg) {
        return _container.upper_bound(seg)->val;
    }

    ComparableSegment* next();

   private:
    container_t _container;
};