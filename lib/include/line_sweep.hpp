#pragma once

#include <event_queue.hpp>
#include <status.hpp>
#include <vector>

constexpr double EPS = 1e-9;  // TODO: Try other numbers

struct Intersection {
    point_t pt;
    std::vector<ComparableSegment> segs;
};

class LineSweep {
    double sweep_line_y;

    EventQueue q;
    Status status;

    std::vector<ComparableSegment> segments;
    std::vector<Intersection> intersections;

   public:
    LineSweep(const std::vector<segment_t>& segments);
    void find_intersections();
    void handleEventPoint(const Event& e);

    void findNewEvent(const ComparableSegment& left, const ComparableSegment& right, const point_t& pt);


    std::vector<Intersection> getIntersections() { return intersections; }
};
