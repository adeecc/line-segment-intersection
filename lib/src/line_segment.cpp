#include <algorithm>
#include <iostream>
#include <line_segment.hpp>
#include <point.hpp>

namespace Geometry {

static inline double det(double a, double b, double c, double d) {
    // |a b|
    // |c d|
    return a * d - b * c;
}

static bool is_internal(const LineSegment& l, const Point& pt) {
    return (((l.u.x <= pt.x and pt.x <= l.v.x) or (l.v.x <= pt.x and pt.x <= l.u.x)) and ((l.u.y <= pt.y and pt.y <= l.v.y) or (l.v.y <= pt.y and pt.y <= l.u.y)));
}

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Geometry::Point p, Geometry::Point q, Geometry::Point r) {
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;

    return false;
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;    // collinear
    return (val > 0) ? 1 : 2;  // clock or counterclock wise
}

bool LineSegment::does_intersect(const LineSegment& l1, const LineSegment& l2) {
    int o1 = orientation(l1.u, l1.v, l2.u);
    int o2 = orientation(l1.u, l1.v, l2.v);
    int o3 = orientation(l2.u, l2.v, l1.u);
    int o4 = orientation(l2.u, l2.v, l1.v);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(l1.u, l2.u, l1.v)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(l1.u, l2.v, l1.v)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(l2.u, l1.u, l2.v)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(l2.u, l1.v, l2.v)) return true;

    return false;
}

Point LineSegment::compute_intersection(const LineSegment& l1, const LineSegment& l2) {
    double a1 = l1.v.y - l1.u.y;
    double b1 = l1.u.x - l1.v.x;
    double c1 = -det(l1.u.x, l1.u.y, l1.v.x, l1.v.y);

    double a2 = l2.v.y - l2.u.y;
    double b2 = l2.u.x - l2.v.x;
    double c2 = -det(l2.u.x, l2.u.y, l2.v.x, l2.v.y);

    double dr = det(a1, b1, a2, b2);

    if (dr == 0) {
        std::cout << "Assertion will fail @LineSegment::compute_intersection: " << l1 << " " << l2 << "\n";
    }

    assert(dr != 0);

    double x = det(b1, c1, b2, c2) / dr;
    double y = det(c1, a1, c2, a2) / dr;

    return Point(x, y);
}

Point LineSegment::compute_intersection(const Point& u, const Point& v, double y) {
    if (u.y == v.y)
        return u;

    double x = v.x + ((y - v.y) * (v.x - u.x) / (v.y - u.y));

    return Point(x, y);
}

Point LineSegment::compute_intersection(const LineSegment& l1, double y) {
    return LineSegment::compute_intersection(l1.u, l1.v, y);
}

}  // namespace Geometry