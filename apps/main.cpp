#include <iostream>
#include <line_sweep.hpp>
#include <rb_tree.hpp>
#include <utils.hpp>
#include <vector>

int main() {
    std::vector<segment_t> segs = Utils::parse_file("input.txt");
    // int count; std::cin >> count;
    // std::vector<segment_t> segs = Utils::TestCaseFactory::random(count, 10);

#ifndef NDEBUG
    std::cout << "Staring Sweep Line Algorithm for: \n";
    for (auto seg : segs) std::cout << seg << "  ";
    std::cout << "\n------------------------------\n";
#endif

    LineSweep sweep(segs);
    sweep.find_intersections();
    auto intersections = sweep.getIntersections();

#ifndef NDEBUG
    std::cout << "Found Following Intersections: \n";
    for (const auto& intersection : intersections) {
        std::cout << intersection << "\n";
    };
#endif

    std::cout << "\nIntersection Count: " << intersections.size() << "\n";

    std::vector<point_t> intersection_pts;
    intersection_pts.reserve(intersections.size());

    for (const auto& its : intersections) {
        intersection_pts.push_back(its.pt);
    }

//    Utils::generate_output("output.txt", segs, intersection_pts);

    return 0;
}
