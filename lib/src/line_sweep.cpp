#include <algorithm>
#include <iostream>
#include <line_sweep.hpp>

LineSweep::LineSweep(const std::vector<segment_t>& segs) {
    segments.reserve(segs.size());

    for (const segment_t& seg : segs) {
        segments.push_back(ComparableSegment(seg.u, seg.v, &sweep_line_y));
    }

    for (ComparableSegment segment : segments) {
        q.insert(Event(segment.u, segment, 0));
        q.insert(Event(segment.v, segment, 1));
    }

#ifndef NDEBUG
    std::cout << "Event Queue: ";
    for (auto it = q.begin(); it != q.end(); ++it) {
        std::cout << (*it).pt << "\t";
    }
    std::cout << "\n\n";
#endif
}

void LineSweep::find_intersections() {
    while (!q.empty()) {
        auto e = q.next();
        handleEventPoint(e);
        // Recalculate the relative_loc for comparable segments in status when encountering the top pt of a new segment?
    }
}

void LineSweep::handleEventPoint(const Event& e) {
    sweep_line_y = e.pt.y;

#ifndef NDEBUG
    std::cout << "Handling Event Point: " << e.pt << "\n";

    std::cout << "lower: ";
    for (const auto& seg : e.lower) std::cout << seg << "\t";
    std::cout << "\n";

    std::cout << "contain: ";
    for (const auto& seg : e.contain) std::cout << seg << "\t";
    std::cout << "\n";

    std::cout << "upper: ";
    for (const auto& seg : e.upper) std::cout << seg << "\t";
    std::cout << "\n------------------------------\n";
#endif

    int total_size = e.lower.size() + e.upper.size() + e.contain.size();
    if (total_size > 1) {
        Intersection I(e.pt);

        for (const auto& comparableSeg : e.lower) {
            I.segs.push_back(comparableSeg);
        }

        for (const auto& comparableSeg : e.upper) {
            I.segs.push_back(comparableSeg);
        }

        for (const auto& comparableSeg : e.contain) {
            I.segs.push_back(comparableSeg);
        }

        intersections.push_back(I);
#ifndef NDEBUG
        std::cout << "Found Intersection point:\n"
                  << I;
        std::cout << "\n------------------------------\n";

#endif
    }

    for (auto comparableSeg : e.lower) {
        status.erase(comparableSeg);
    }

    for (const auto& comparableSeg : e.contain) {
        status.erase(comparableSeg);
    }

    double leftMostIntersect = std::numeric_limits<int>::max(), rightMostIntersect = std::numeric_limits<int>::min();

    // Insert U(p) | C(p) into Status in their order slightly below l
    sweep_line_y += 2 * EPS;
    for (auto& seg : e.upper) {
        point_t sweep_line_intersection = ComparableSegment::compute_intersection(seg, sweep_line_y);
        leftMostIntersect = std::min(leftMostIntersect, sweep_line_intersection.x);
        rightMostIntersect = std::min(rightMostIntersect, sweep_line_intersection.x);

        status.insert(seg);
    }

    for (auto& seg : e.contain) {
        point_t sweep_line_intersection = ComparableSegment::compute_intersection(seg, sweep_line_y);
        leftMostIntersect = std::min(leftMostIntersect, sweep_line_intersection.x);
        rightMostIntersect = std::min(rightMostIntersect, sweep_line_intersection.x);

        status.insert(seg);
    }
    sweep_line_y -= 2 * EPS;  // FIXME: Is this reset required?

    if (e.upper.size() + e.contain.size() == 0) {
        // This must mean that p is a lower point only,
        // and not the upper point or intersection point of any segment
        // So, Get Left and Right neighbour to check

        Status::iterator b_right = status.upper_bound(ComparableSegment(e.pt, e.pt, &sweep_line_y));
        if (b_right != status.end() and b_right != status.begin()) {  // FIXME: Are both checks required?
            Status::iterator b_left = b_right--;
#ifndef NDEBUG
            std::cout << "[" << e.pt << "] "
                      << "b_left: " << *b_left << "b_right: " << *b_right << "\n";
#endif
            findNewEvent(*b_left, *b_right, e.pt);
        }
#ifndef NDEBUG
        else {
            std::cout << "[" << e.pt << "] "
                      << "b_right = " << (b_right == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
        }
#endif

    } else {
        point_t left(leftMostIntersect - 2 * EPS, sweep_line_y),
            right(rightMostIntersect + 2 * EPS, sweep_line_y);

        Status::iterator s_left = status.upper_bound(ComparableSegment(left, left, &sweep_line_y));
        Status::iterator b_right = status.upper_bound(ComparableSegment(right, right, &sweep_line_y));

        if (s_left != status.end() and s_left != status.begin()) {
            Status::iterator b_left = s_left--;
            findNewEvent(*b_left, *s_left, e.pt);
        }
#ifndef NDEBUG
        else {
            std::cout << "[" << e.pt << "] "
                      << "s_left = " << (s_left == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
        }
#endif

        if (b_right != status.end() and b_right != status.begin()) {
            Status::iterator s_right = b_right--;
            findNewEvent(*s_right, *b_right, e.pt);
        }
#ifndef NDEBUG
        else {
            std::cout << "[" << e.pt << "] "
                      << "b_right = " << (b_right == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
        }

#endif
    }
}

void LineSweep::findNewEvent(const ComparableSegment& leftNeighbour, const ComparableSegment& rightNeighbour, const point_t& pt) {
    if (!segment_t::does_intersect(leftNeighbour, rightNeighbour)) {
#ifndef NDEBUG
        std::cout << "[" << pt << "] (findNewEvent): "
                  << leftNeighbour << " does not intersect with" << rightNeighbour << "\n";

#endif
        return;
    }
    point_t intersection = segment_t::compute_intersection(leftNeighbour, rightNeighbour);

    // If intersection is below sweep_line or to the right of the event point
    if ((intersection.y < sweep_line_y) or (intersection.x > pt.x)) {
        if (q.find(Event(intersection, ComparableSegment(), 3)) != q.end()) {
            if (pt != leftNeighbour.u and pt != leftNeighbour.v) q.insert(Event(pt, leftNeighbour, 2));
            if (pt != rightNeighbour.u and pt != rightNeighbour.v) q.insert(Event(pt, rightNeighbour, 2));
        }
    }
}