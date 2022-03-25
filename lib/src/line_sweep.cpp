#include <algorithm>
#include <iostream>
#include <line_sweep.hpp>

LineSweep::LineSweep(const std::vector<segment_t>& segs) {
    segments.reserve(segs.size());

    for (const segment_t& seg : segs) {
        segments.push_back(ComparableSegment(seg.u, seg.v, &sweep_line_y));
    }

    for (ComparableSegment segment : segments) {
        q.insert(Event(segment.top(), segment, Event::Type::UPPER));
        q.insert(Event(segment.bottom(), segment, Event::Type::LOWER));
    }

#ifndef NDEBUG
    std::cout << "Event Queue: ";
    for (auto it = q.begin(); it != q.end(); ++it) {
        std::cout << (*it).pt << " ";
    }
    std::cout << "\n\n";
#endif
}

void LineSweep::find_intersections() {
    while (!q.empty()) {
        auto e = q.next();
        handleEventPoint(e);
    }
}

void LineSweep::_findTrivialIntersection(const Event& e) {
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
        std::cout << "Found Intersection point:\n"
                  << I;
        std::cout << "\n------------------------------\n";
    }
}

void LineSweep::_eraseConsideredPoints(const Event& e) {
    std::cout << "[" << e.pt << "] "
              << "Erasing from status...\n";

    for (auto seg : e.lower) {
        std::cout << "Erased: " << seg << "\n";
        status.erase(seg);
    }

    for (const auto& seg : e.contain) {
        std::cout << "Erased: " << seg << "\n";
        status.erase(seg);
    }
}

void LineSweep::_insertNewPoints(const Event& e) {
    std::cout << "[" << e.pt << "] "
              << "Inserting into status...\n";

    // Insert U(p) | C(p) into Status in their order **slightly below l**
    sweep_line_y += 2 * EPS;
    for (auto& seg : e.upper) {
        std::cout << "Inserted: " << seg << "\n";
        status.insert(seg);
    }

    for (auto& seg : e.contain) {
        std::cout << "Inserted: " << seg << "\n";
        status.insert(seg);
    }

    sweep_line_y -= 2 * EPS;  // FIXME: Is this reset required?
}

double LineSweep::_findLeftMostIntersection(const std::vector<ComparableSegment>& segs) {
    double mn = std::numeric_limits<int>::max();

    for (const ComparableSegment& seg : segs) {
        double its_x = ComparableSegment::compute_intersection(seg, sweep_line_y).x;
        mn = std::min(mn, its_x);
    }

    return mn;
}

double LineSweep::_findRightMostIntersection(const std::vector<ComparableSegment>& segs) {
    double mx = std::numeric_limits<int>::min();

    for (const ComparableSegment& seg : segs) {
        double its_x = ComparableSegment::compute_intersection(seg, sweep_line_y).x;
        mx = std::max(mx, its_x);
    }

    return mx;
}

void LineSweep::_handleLowerOnlyPoint(const Event& e) {
    Status::iterator b_right = status.upper_bound(ComparableSegment(e.pt, e.pt, &sweep_line_y));

    // If b_right = status.end() then search was unsuccesful.
    // If b_right = status.begin() then there is no item smaller and we can not decrement the iterator.
    if (b_right != status.end() and b_right != status.begin()) {
        Status::iterator b_left = b_right;
        b_left--;

        std::cout << "[" << e.pt << "] "
                  << "b_left: " << *b_left << "b_right: " << *b_right << "\n";
        findNewEvent(*b_left, *b_right, e.pt);
    } else {
        std::cout << "[" << e.pt << "] "
                  << "b_right = " << (b_right == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
    }
}

// All lines segments which are also vertical, are processes separately

void LineSweep::_handleIsUpperContainPoint(const Event& e) {
    double leftMostIntersect =
        std::min(_findLeftMostIntersection(e.upper), _findLeftMostIntersection(e.contain));

    double rightMostIntersect =
        std::max(_findRightMostIntersection(e.upper), _findRightMostIntersection(e.contain));

    point_t left(leftMostIntersect - 2 * EPS, sweep_line_y),
        right(rightMostIntersect + 2 * EPS, sweep_line_y);

    Status::iterator s_left = status.upper_bound(ComparableSegment(left, left, &sweep_line_y));
    Status::iterator b_right = status.upper_bound(ComparableSegment(right, right, &sweep_line_y));

    if (s_left != status.end() and s_left != status.begin()) {
        Status::iterator b_left = s_left;
        b_left--;
        findNewEvent(*b_left, *s_left, e.pt);
    } else {
        std::cout << "[" << e.pt << "] "
                  << "s_left = " << (s_left == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
    }

    if (b_right != status.end() and b_right != status.begin()) {
        Status::iterator s_right = b_right;
        s_right--;
        findNewEvent(*s_right, *b_right, e.pt);
    } else {
        std::cout << "[" << e.pt << "] "
                  << "b_right = " << (b_right == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
    }
}

void LineSweep::handleEventPoint(const Event& e) {
    sweep_line_y = e.pt.y;

    std::cout << "Handling Event Point: " << e.pt << "\n";

    std::cout << "lower: ";
    for (const auto& seg : e.lower) std::cout << seg << "\t";
    std::cout << "\n";

    std::cout << "contain: ";
    for (const auto& seg : e.contain) std::cout << seg << "\t";
    std::cout << "\n";

    std::cout << "upper: ";
    for (const auto& seg : e.upper) std::cout << seg << "\n";

    std::cout << "Final Status Queue: {";
    for (auto seg : status) {
        std::cout << seg << "    ";
    }
    std::cout << "}\n\n";

    _findTrivialIntersection(e);
    _eraseConsideredPoints(e);
    _insertNewPoints(e);

    std::cout << "Final Status Queue: {";
    for (auto seg : status) {
        std::cout << seg << "    ";
    }
    std::cout << "}\n\n";

    if (e.upper.size() + e.contain.size() == 0) {
        // This must mean that p is a lower point only,
        // and not the upper point or intersection point of any segment
        // So, Get Left and Right neighbour to check
        _handleLowerOnlyPoint(e);
    } else {
        _handleIsUpperContainPoint(e);
    }

    std::cout << "\n------------------------------\n";
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
        if (intersection != leftNeighbour.u and intersection != leftNeighbour.v)
            q.insert(Event(intersection, leftNeighbour, Event::Type::CONTAIN));
        if (intersection != rightNeighbour.u and intersection != rightNeighbour.v)
            q.insert(Event(intersection, rightNeighbour, Event::Type::CONTAIN));
    }
}