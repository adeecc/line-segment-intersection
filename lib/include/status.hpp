/**
 * @file status.hpp
 * @brief Status Queue Implementation
 */
#pragma once
#include <comparable_segment.hpp>
#include <rb_tree.hpp>

///Type Alias for Point
using point_t = Geometry::Point;
///Type Alias for Line Segment
using segment_t = Geometry::LineSegment;

/**
 * @brief A struct for mainting a Status queue of Line Segments 
 * 
 */
struct Status {

    ///Type Alias for rb-tree node
    using node_type = DS::rb_tree::node_t<ComparableSegment>;
    ///Type Alias for rb-tree tree
    using container_type = DS::rb_tree::tree_t<ComparableSegment>;
    ///Type Alias for rb-tree iterator
    using iterator = DS::rb_tree::iterator_t<node_type>;
    
    /**
     * @brief This method inserts the segment in the Status queue
     * 
     * @param seg is the current segment to be inserted
     */
    void insert(const ComparableSegment& seg) {
        _container.insert(seg);
    }

    /**
     * @brief This method removes the segment from the Status queue
     * 
     * @param seg is the current segment to be removed
     */

    void erase(const ComparableSegment& seg) {
        _container.erase(seg);
    }

    /**
     * @brief This method defines a lower bound on a segment
     * 
     * @param seg 
     * @return iterator to the smallest element greater than or equal to the seg in the Status queue
     */
    iterator lower_bound(const ComparableSegment& seg) {
        return _container.lower_bound(seg);
    }

    /**
     * @brief This method defines an upper bound on a segment
     * 
     * @param seg 
     * @return iterator to smallest element strictly greater than seg in the Status queue
     */
    iterator upper_bound(const ComparableSegment& seg) {
        return _container.upper_bound(seg);
    }

    /**
     * @brief Obtaining the first segment in the Status queue
     * 
     * @return iterator to the first element in the queue
     */
    iterator begin() { return _container.begin(); }

    /**
     * @brief Obtaining the last segment in the Status queue
     * 
     * @return iterator to the last element in the queue 
     */
    iterator end() { return _container.end(); }

   
   private:
   // Initializing a variable of Type container_type
    container_type _container;
};