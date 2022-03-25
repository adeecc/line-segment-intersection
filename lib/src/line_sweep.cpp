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
        Intersection I;
        I.pt = e.pt;
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
        std::cout << "Found Intersection point: " << e.pt;
        std::cout << "\n------------------------------\n";

#endif
    }

    for (auto comparableSeg : e.lower) {
        status.erase(comparableSeg);
    }

    for (const auto& comparableSeg : e.contain) {
        status.erase(comparableSeg);
    }

    // Insert U(p) | C(p) into Status in their order slightly below l
    sweep_line_y += 2 * EPS;
    for (auto& comparableSeg : e.upper) {
        status.insert(comparableSeg);
    }

    for (auto& comparableSeg : e.contain) {
        status.insert(comparableSeg);
    }

    if (e.upper.size() + e.contain.size() == 0) {
        // This must mean that p is a lower point only,
        // and not the upper point or intersection point of any segment
        // So, Get Left and Right neighbour to check

        Status::iterator_type rightNeighbour = status.upper_bound(ComparableSegment(e.pt, e.pt, &sweep_line_y));
        if (rightNeighbour != status.end() and rightNeighbour != status.begin()) {
            // TODO: Check if the predecssor exists?
            Status::iterator_type leftNeighbour = rightNeighbour--;
            findNewEvent(leftNeighbour->val, rightNeighbour->val, e.pt);
        }

    } else {
        ComparableSegment leftmost, rightmost;
        if (e.upper.size()) {
            leftmost = e.upper[0];
            rightmost = e.upper[0];
        } else {
            leftmost = e.contain[0];
            rightmost = e.contain[0];
        }

        for (const auto& seg : e.upper) {
            auto leftmost_intersection = segment_t::compute_intersection(leftmost, e.pt.y);
            auto rightmost_intersection = segment_t::compute_intersection(rightmost, e.pt.y);
            auto seg_intersection = segment_t::compute_intersection(seg, e.pt.y);

            if (seg_intersection.x < leftmost_intersection.x) leftmost = seg;
            if (seg_intersection.x > rightmost_intersection.x) rightmost = seg;
        }

        for (const auto& seg : e.contain) {
            // Move the leftmost and rightmost segments slightly to get the correct items
            auto leftmost_intersection = segment_t::compute_intersection(leftmost, e.pt.y);
            auto rightmost_intersection = segment_t::compute_intersection(rightmost, e.pt.y);
            auto seg_intersection = segment_t::compute_intersection(seg, e.pt.y);

            if (seg_intersection.x < leftmost_intersection.x) leftmost = seg;
            if (seg_intersection.x > rightmost_intersection.x) rightmost = seg;
        }

        Status::iterator_type leftNeighbour = status.upper_bound(leftmost);    // --leftNeighbour;
        Status::iterator_type rightNeighbour = status.upper_bound(rightmost);  // --rightNeighbour;

        if (leftNeighbour != status.end() && rightNeighbour != status.end())
            findNewEvent(leftNeighbour->val, rightNeighbour->val, e.pt);
    }
}

void LineSweep::findNewEvent(const ComparableSegment& leftNeighbour, const ComparableSegment& rightNeighbour, const point_t& pt) {
    if (!segment_t::does_intersect(leftNeighbour, rightNeighbour)) return;
    point_t intersection = segment_t::compute_intersection(leftNeighbour, rightNeighbour);

    // If intersection is below sweep_line or to the right of the event point
    if ((intersection.y < sweep_line_y) or (intersection.x > pt.x)) {
        if (q.find(Event(intersection, ComparableSegment(), 3)) != q.end()) {
            if (pt != leftNeighbour.u and pt != leftNeighbour.v) q.insert(Event(pt, leftNeighbour, 2));
            if (pt != rightNeighbour.u and pt != rightNeighbour.v) q.insert(Event(pt, rightNeighbour, 2));
        }
    }
}