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
    std::vector<ComparableSegment*> segments;
    std::vector<Intersection> intersections;

   public:
    LineSweep(std::vector<segment_t>& segments);
    void find_intersections();
    void handleEventPoint(Event* e);

    void findNewEvent(ComparableSegment* left, ComparableSegment* right, point_t* pt);

    std::vector<Intersection> getIntersections() { return intersections; }
};
