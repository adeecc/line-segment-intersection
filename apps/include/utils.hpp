#pragma once

#include <fstream>
#include <iostream>
#include <line_segment.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace Utils {

using point_t = Geometry::Point;
using segment_t = Geometry::LineSegment;

std::vector<segment_t> parse_file(const std::string& fname) {
    std::ifstream stream(fname);

    if (!stream) {
        std::cerr << "Could not parse file: " << fname << "\n";
        return {};
    }

    int n;
    stream >> n;

    std::vector<segment_t> segments(n);
    for (auto& seg : segments) {
        double ux, uy, vx, vy;
        stream >> ux >> uy >> vx >> vy;
        seg = segment_t(ux, uy, vx, vy);

#ifndef NDEBUG
        std::cout << "Scanned Segment: " << seg << "\n";
#endif
    }

    stream.close();
    return segments;
}

void generate_output(std::string fname, const std::vector<segment_t>& segs, const std::vector<point_t>& intersections) {
    std::ofstream stream(fname);

    stream << segs.size() << "\n";
    for (const segment_t& seg : segs) {
        stream << seg.u.x << " " << seg.u.y << " " << seg.v.x << " " << seg.v.x << "\n";
    }

    stream << intersections.size() << "\n";
    for (const point_t& its : intersections) {
        stream << its.x << " " << its.y << "\n";
    }

    stream.close();
}

}  // namespace Utils