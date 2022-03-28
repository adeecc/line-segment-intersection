/**
 * @file line_sweep.hpp
 * @brief Define the intersection data structure and implementation of Bentley-Ottman Algorithm
 */
#pragma once

#include <event_queue.hpp>
#include <iomanip>
#include <status.hpp>
#include <vector>

/**
 * @brief Stores the intersection points and the segments intersecting
 *
 */
struct Intersection {
    /// The point of intersection
    point_t pt;

    /// List of Segments intersecting at point
    std::vector<ComparableSegment> segs;

    /**
     * @brief Construct a new Intersection object
     *
     */
    Intersection() = default;

    /**
     * @brief Construct a new Intersection object
     *
     * @param pt point of intersection
     */
    explicit Intersection(const point_t& pt) : pt(pt) {}

    /**
     * @brief Overloading the operator<<
     *
     * @param stream Output Stream to be written on
     * @param intersection intersection to write
     * @return std::ostream& reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& stream, const Intersection& intersection) {
        stream << intersection.pt << ": {";
        for (const auto& segs : intersection.segs) stream << segs << "\t\t";
        stream << "}\n";
        return stream;
    }
};

/**
 * @brief Implementation of the Bentley-Ottman algorithm.
 * Refer to Bentley, J. L.; Ottmann, T. A. (1979), "Algorithms for reporting and counting geometric intersections" for more details
 *
 */
class LineSweep {
    /// Epsilon to be used for the Bentley-Ottman algorithm
    /// Delta to be taken when calculatingn the neighbours at an intersection point
    static constexpr double EPS = std::numeric_limits<float>::epsilon();

    /// Current sweep line position
    double sweep_line_y{};

    /// EventQueue data structure
    EventQueue q;

    /// Status datastructure
    Status status;

    /// Set of segments being evaluated
    std::vector<ComparableSegment> segments;

    /// List of calculated intersection points
    std::vector<Intersection> intersections;

    void _findTrivialIntersection(const Event& e);
    void _eraseConsideredPoints(const Event& e);
    void _insertNewPoints(const Event& e);
    double _findLeftMostIntersection(const std::vector<ComparableSegment>& segs) const;
    double _findRightMostIntersection(const std::vector<ComparableSegment>& segs) const;
    void _handleLowerOnlyPoint(const Event& e);
    void _handleIsUpperContainPoint(const Event& e);

    void _handleEventPoint(const Event& e);
    void _findNewEvent(const ComparableSegment& left, const ComparableSegment& right, const point_t& pt);

   public:
    /**
     * @brief Construct a LineSweep object
     *
     * @param segments Line Segments to be evaluated
     */
    explicit LineSweep(const std::vector<segment_t>& segments);

    /**
     * @brief Compute the intersections over the segments
     *
     */
    void find_intersections();

    /**
     * @brief Get all computed intersections
     *
     * @return the calculated intersection points
     */
    std::vector<Intersection> getIntersections() { return intersections; }
};
