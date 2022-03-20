#pragma once

#include <comparable_segment.hpp>
#include <rb_tree.hpp>

using point_t = Geometry::Point;
using segment_t = Geometry::LineSegment;

struct Status {
    using container_t = DS::rb_tree::tree_t<ComparableSegment, ComparableSegment*>;
    using node_t = DS::rb_tree::node_t<ComparableSegment, ComparableSegment*>;

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

    node_t* begin() { return _container.begin(); }
    node_t* end() { return _container.end(); }

    node_t* predecessor(ComparableSegment seg) { return _container.predecessor(seg); }
    node_t* successor(ComparableSegment seg) { return _container.successor(seg); }

   private:
    container_t _container;
};