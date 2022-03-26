#pragma once

#include <event_queue.hpp>
#include <iomanip>
#include <status.hpp>
#include <vector>

struct Intersection {
    point_t pt;
    std::vector<ComparableSegment> segs;

    Intersection() = default;
    explicit Intersection(const point_t& pt) : pt(pt) {}

    friend std::ostream& operator<<(std::ostream& stream, const Intersection& intersection) {
        stream << intersection.pt << ": {";
        for (const auto& segs : intersection.segs) stream << segs << "\t\t";
        stream << "}\n";
        return stream;
    }
};

class LineSweep {
    static constexpr double EPS = std::numeric_limits<float>::epsilon();  // TODO: Try other options

    double sweep_line_y{};

    EventQueue q;
    Status status;

    std::vector<ComparableSegment> segments;
    std::vector<Intersection> intersections;

    void _findTrivialIntersection(const Event& e);
    void _eraseConsideredPoints(const Event& e);
    void _insertNewPoints(const Event& e);
    double _findLeftMostIntersection(const std::vector<ComparableSegment>& segs) const;
    double _findRightMostIntersection(const std::vector<ComparableSegment>& segs) const;
    void _handleLowerOnlyPoint(const Event& e);
    void _handleIsUpperContainPoint(const Event& e);

   public:
    explicit LineSweep(const std::vector<segment_t>& segments);
    void find_intersections();
    void handleEventPoint(const Event& e);

    void findNewEvent(const ComparableSegment& left, const ComparableSegment& right, const point_t& pt);

    std::vector<Intersection> getIntersections() { return intersections; }
};
