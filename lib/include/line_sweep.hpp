#pragma once

#include <event_queue.hpp>
#include <status.hpp>
#include <vector>

const double EPS = 1e-9;  // TODO: Try other numbers

struct Intersection {
    point_t pt;
    std::vector<ComparableSegment> segs;

    Intersection() {}
    Intersection(const point_t& pt) : pt(pt) {}

    friend std::ostream& operator<<(std::ostream& stream, const Intersection& intersection) {
        stream << "<" << intersection.pt << ">: {";
        for (const auto& segs : intersection.segs) stream << segs << "\t";
        stream << "}\n";
        return stream;
    }
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
