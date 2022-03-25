#pragma once

#include <comparable_segment.hpp>
#include <rb_tree.hpp>

using point_t = Geometry::Point;
using segment_t = Geometry::LineSegment;

struct Status {
    using node_type = DS::rb_tree::node_t<ComparableSegment>;
    using container_type = DS::rb_tree::tree_t<ComparableSegment>;
    using iterator = DS::rb_tree::iterator_t<node_type>;

    void insert(const ComparableSegment& seg) {
        _container.insert(seg);
    }

    void erase(const ComparableSegment& seg) {
        _container.erase(seg);
    }

    iterator lower_bound(const ComparableSegment& seg) {
        return _container.lower_bound(seg);
    }

    iterator upper_bound(const ComparableSegment& seg) {
        return _container.upper_bound(seg);
    }

    iterator begin() { return _container.begin(); }
    iterator end() { return _container.end(); }

   private:
    container_type _container;
};