#include <iostream>
#include <line_sweep.hpp>

LineSweep::LineSweep(std::vector<segment_t>& segs) {
    segments.reserve(segs.size());

    for (const auto& seg : segs) {
        segments.push_back(new ComparableSegment(seg.u, seg.v, &sweep_line_y));
    }

    for (auto segment : segments) {
        q.insert(segment->u, new Event(&segment->u, segment, 0));
        q.insert(segment->v, new Event(&segment->v, segment, 1));
    }
}

void LineSweep::find_intersections() {
    while (!q.empty()) {
        auto e = q.next();
        handleEventPoint(e);
        // Recalculate the relative_loc for comparable segments in status when encountering the top pt of a new segment?
    }
}

void LineSweep::handleEventPoint(Event* e) {
    sweep_line_y = e->pt->y;

#ifdef DEBUG
    std::cout << "Handling Event Point: " << *e->pt << "\n";

    std::cout << "lower: ";
    for (const auto& seg : e->lower) std::cout << *seg << "\t";
    std::cout << "\n";

    std::cout << "contain: ";
    for (const auto& seg : e->contain) std::cout << *seg << "\t";
    std::cout << "\n";

    std::cout << "upper: ";
    for (const auto& seg : e->upper) std::cout << *seg << "\t";
    std::cout << "\n------------------------------\n";
#endif

    int total_size = e->lower.size() + e->upper.size() + e->contain.size();
    if (total_size > 1) {
        Intersection I;
        I.pt = *e->pt;
        for (const auto& comparableSeg : e->lower) {
            I.segs.push_back(*comparableSeg);
        }

        for (const auto& comparableSeg : e->upper) {
            I.segs.push_back(*comparableSeg);
        }

        for (const auto& comparableSeg : e->contain) {
            I.segs.push_back(*comparableSeg);
        }

        intersections.push_back(I);
#ifdef DEBUG
        std::cout << "Found Intersection point: " << e->pt;
        std::cout << "\n------------------------------\n";

#endif
    }

    for (auto comparableSeg : e->lower) {
        status.erase(*comparableSeg);
    }

    for (const auto& comparableSeg : e->contain) {
        status.erase(*comparableSeg);
    }

    // Insert U(p) | C(p) into Status in their order slightly below l
    sweep_line_y += 2 * EPS;
    for (auto& comparableSeg : e->upper) {
        status.insert(comparableSeg);
    }

    for (auto& comparableSeg : e->contain) {
        status.insert(comparableSeg);
    }

    if (e->upper.size() + e->contain.size() == 0) {
        // This must mean that p is a lower point only,
        // and not the upper point or intersection point of any segment
        // So, Get Left and Right neighbour to check

        auto rightNeighbour = status.upper_bound(ComparableSegment(*e->pt, *e->pt, &sweep_line_y));
        auto leftNeighbour = rightNeighbour--;  // TODO: Check if the predecssor exists?

        findNewEvent(leftNeighbour, rightNeighbour, e->pt);
    } else {
        ComparableSegment leftmost, rightmost;
        if (e->upper.size()) {
            leftmost = *(e->upper[0]);
            rightmost = *(e->upper[0]);
        } else {
            leftmost = *(e->contain[0]);
            rightmost = *(e->contain[0]);
        }

        for (const auto& seg : e->upper) {
            auto leftmost_intersection = segment_t::compute_intersection(leftmost, e->pt->y);
            auto rightmost_intersection = segment_t::compute_intersection(rightmost, e->pt->y);
            auto seg_intersection = segment_t::compute_intersection(*seg, e->pt->y);

            if (seg_intersection.x < leftmost_intersection.x) leftmost = *seg;
            if (seg_intersection.x > rightmost_intersection.x) rightmost = *seg;
        }

        for (const auto& seg : e->contain) {
            // Move the leftmost and rightmost segments slightly to get the correct items
            auto leftmost_intersection = segment_t::compute_intersection(leftmost, e->pt->y);
            auto rightmost_intersection = segment_t::compute_intersection(rightmost, e->pt->y);
            auto seg_intersection = segment_t::compute_intersection(*seg, e->pt->y);

            if (seg_intersection.x < leftmost_intersection.x) leftmost = *seg;
            if (seg_intersection.x > rightmost_intersection.x) rightmost = *seg;
        }

        auto leftNeighbour = status.upper_bound(leftmost);    // --leftNeighbour;
        auto rightNeighbour = status.upper_bound(rightmost);  // --rightNeighbour;

        findNewEvent(leftNeighbour, rightNeighbour, e->pt);
    }
}

void LineSweep::findNewEvent(ComparableSegment* leftNeighbour, ComparableSegment* rightNeighbour, point_t* pt) {
    if (!segment_t::does_intersect(*leftNeighbour, *rightNeighbour)) return;
    point_t intersection = segment_t::compute_intersection(*leftNeighbour, *rightNeighbour);

    // If intersection is below sweep_line or to the right of the event point
    if ((intersection.y < sweep_line_y) or (intersection.x > pt->x)) {
        if (q.search(intersection) != q.end()) {
            if (*pt != leftNeighbour->u and *pt != leftNeighbour->v) q.insert(*pt, new Event(pt, leftNeighbour, 2));
            if (*pt != rightNeighbour->u and *pt != rightNeighbour->v) q.insert(*pt, new Event(pt, rightNeighbour, 2));
        }
    }
}