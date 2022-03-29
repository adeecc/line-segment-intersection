#include <algorithm>
#include <iostream>
#include <line_sweep.hpp>

LineSweep::LineSweep(const std::vector<segment_t>& segs) {
    segments.reserve(segs.size());

    for (const segment_t& seg : segs) {
        segments.emplace_back(seg.u, seg.v, &sweep_line_y);
    }

    for (ComparableSegment segment : segments) {
        q.insert(Event(segment.top(), segment, Event::Type::UPPER));
        q.insert(Event(segment.bottom(), segment, Event::Type::LOWER));
    }

#ifndef NDEBUG
    std::cout << "Event Queue: ";
    for (auto& it : q) {
        std::cout << it.pt << " ";
    }
    std::cout << "\n\n";
#endif
}

void LineSweep::find_intersections() {
    while (!q.empty()) {
        auto e = q.next();
        _handleEventPoint(e);
    }
}

void LineSweep::_findTrivialIntersection(const Event& e) {
    size_t total_size = e.lower.size() + e.upper.size() + e.contain.size();
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

        intersections.insert(I);

#ifndef NDEBUG

        std::cout << "Found Intersection point: " << I << "\n";
#endif
    }
}

void LineSweep::_eraseConsideredPoints(const Event& e) {
#ifndef NDEBUG

    std::cout << "[" << e.pt << "] (_eraseConsideredPoints): "
              << "Erasing from status...\n";
#endif

    for (auto seg : e.lower) {
#ifndef NDEBUG
        std::cout << "Erased: " << seg << "\n";
#endif
        status.erase(seg);
    }

    for (const auto& seg : e.contain) {
#ifndef NDEBUG
        std::cout << "Erased: " << seg << "\n";
#endif
        status.erase(seg);
    }
}

void LineSweep::_insertNewPoints(const Event& e) {
#ifndef NDEBUG

    std::cout << "[" << e.pt << "] (_insertNewPoints): "
              << "Inserting into status...\n";
#endif
    // Insert U(p) | C(p) into Status in their order **slightly below l**
    sweep_line_y -= 2 * LineSweep::EPS;
    for (const ComparableSegment& seg : e.upper) {
#ifndef NDEBUG
        std::cout << "Inserted: " << seg << "\n";
#endif
        status.insert(seg);
    }

    for (const ComparableSegment& seg : e.contain) {
#ifndef NDEBUG
        std::cout << "Inserted: " << seg << "\n";
#endif
        status.insert(seg);
    }

    // sweep_line_y -= 2 * LineSweep::EPS;  // FIXME: Is this reset required?
}

double LineSweep::_findLeftMostIntersection(const std::vector<ComparableSegment>& segs) const {
    double mn = std::numeric_limits<int>::max();

    for (const ComparableSegment& seg : segs) {
        double its_x = ComparableSegment::compute_intersection(seg, sweep_line_y).x;
        mn = std::min(mn, its_x);
    }

    return mn;
}

double LineSweep::_findRightMostIntersection(const std::vector<ComparableSegment>& segs) const {
    double mx = std::numeric_limits<int>::min();

    for (const ComparableSegment& seg : segs) {
        double its_x = ComparableSegment::compute_intersection(seg, sweep_line_y).x;
        mx = std::max(mx, its_x);
    }

    return mx;
}

void LineSweep::_handleLowerOnlyPoint(const Event& e) {
    Status::iterator b_right = status.upper_bound(ComparableSegment(e.pt, e.pt, &sweep_line_y));

    // If b_right = status.end() then search was unsuccessful.
    // If b_right = status.begin() then there is no item smaller, and we can not decrement the iterator.
    if (b_right != status.end() and b_right != status.begin()) {
        Status::iterator b_left = b_right;
        b_left--;
#ifndef NDEBUG
        std::cout << "[" << e.pt << "] (_handleLowerOnlyPoint): "
                  << "b_left: " << *b_left << " b_right: " << *b_right << "\n";
#endif
        _findNewEvent(*b_left, *b_right, e.pt);
    } else {
#ifndef NDEBUG
        std::cout << "[" << e.pt << "] (_handleLowerOnlyPoint): "
                  << "b_right = " << (b_right == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
#endif
    }
}

// All lines segments which are also vertical, are processes separately

void LineSweep::_handleIsUpperContainPoint(const Event& e) {
    double leftMostIntersect =
        std::min(_findLeftMostIntersection(e.upper), _findLeftMostIntersection(e.contain));

    double rightMostIntersect =
        std::max(_findRightMostIntersection(e.upper), _findRightMostIntersection(e.contain));

    point_t left(leftMostIntersect - 2 * LineSweep::EPS, sweep_line_y),
        right(rightMostIntersect + 2 * LineSweep::EPS, sweep_line_y);

    Status::iterator s_left = status.upper_bound(ComparableSegment(left, left, &sweep_line_y));
    Status::iterator b_right = status.upper_bound(ComparableSegment(right, right, &sweep_line_y));

    if (s_left != status.end() and s_left != status.begin()) {
        Status::iterator b_left = s_left;
        b_left--;
#ifndef NDEBUG
        std::cout << "[" << e.pt << "] (_handleIsUpperContainPoint:left): "
                  << "b_left: " << *b_left << " s_left: " << *s_left << "\n";
#endif
        _findNewEvent(*b_left, *s_left, e.pt);
    } else {
#ifndef NDEBUG
        std::cout << "[" << e.pt << "] (_handleIsUpperContainPoint:left): "
                  << "s_left = " << (s_left == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
#endif
    }

    if (b_right != status.end() and b_right != status.begin()) {
        Status::iterator s_right = b_right;
        s_right--;
#ifndef NDEBUG
        std::cout << "[" << e.pt << "] (_handleIsUpperContainPoint:right): "
                  << "s_right: " << *s_right << " b_right: " << *b_right << "\n";
#endif
        _findNewEvent(*s_right, *b_right, e.pt);
    } else {
#ifndef NDEBUG
        std::cout << "[" << e.pt << "] (_handleIsUpperContainPoint:right): "
                  << "b_right = " << (b_right == status.end() ? "status.end()" : "status.begin()") << ". Skipping\n";
#endif
    }
}

void LineSweep::_handleEventPoint(const Event& e) {
    sweep_line_y = e.pt.y;

#ifndef NDEBUG
    std::cout << "Handling Event Point: " << e.pt << "\n";
    std::cout << "Sweep Line: y = " << e.pt.y << "\n";

    std::cout << "lower: ";
    for (const auto& seg : e.lower) std::cout << seg << " ";
    std::cout << "\n";

    std::cout << "contain: ";
    for (const auto& seg : e.contain) std::cout << seg << " ";
    std::cout << "\n";

    std::cout << "upper: ";
    for (const auto& seg : e.upper) std::cout << seg << " ";
    std::cout << "\n";

    std::cout << "Initial Status Queue: {";
    for (auto seg : status) {
        std::cout << seg << "    ";
    }
    std::cout << "}\n\n";
#endif

    _findTrivialIntersection(e);
    _eraseConsideredPoints(e);
    _insertNewPoints(e);

#ifndef NDEBUG
    std::cout << "Final Status Queue: {";
    for (auto seg : status) {
        std::cout << seg << "    ";
    }
    std::cout << "}\n\n";
#endif

    if (e.upper.size() + e.contain.size() == 0) {
        // This must mean that p is a lower point only,
        // and not the upper point or intersection point of any segment
        // So, Get Left and Right neighbour to check
        _handleLowerOnlyPoint(e);
    } else {
        _handleIsUpperContainPoint(e);
    }
#ifndef NDEBUG
    std::cout << "\n------------------------------\n";
#endif
}

void LineSweep::_findNewEvent(const ComparableSegment& leftNeighbour, const ComparableSegment& rightNeighbour, const point_t& pt) {
    if (!segment_t::does_intersect(leftNeighbour, rightNeighbour)) {
#ifndef NDEBUG
        std::cout << "[" << pt << "] (findNewEvent): "
                  << leftNeighbour << " does not intersect with" << rightNeighbour << "\n";
#endif
        return;
    }

#ifndef NDEBUG
    std::cout << "[" << pt << "] (findNewEvent): "
              << leftNeighbour << " intersects " << rightNeighbour << "\n";
#endif
    point_t intersection = segment_t::compute_intersection(leftNeighbour, rightNeighbour);

    // If intersection is below sweep_line or to the right of the event point
    if ((intersection.y < pt.y) or (intersection.x > pt.x)) {
#ifndef NDEBUG
    std::cout << "Found New Event Point: " << intersection << "\n";
#endif
    if (intersection != leftNeighbour.u and intersection != leftNeighbour.v)
        q.insert(Event(intersection, leftNeighbour, Event::Type::CONTAIN));
    if (intersection != rightNeighbour.u and intersection != rightNeighbour.v)
        q.insert(Event(intersection, rightNeighbour, Event::Type::CONTAIN));
    }
}

std::vector<Intersection> LineSweep::getIntersections() {
    std::vector<Intersection> segment_list(intersections.begin(), intersections.end());
    return segment_list;
}