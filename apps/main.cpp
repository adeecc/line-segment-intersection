#include <iostream>
#include <line_sweep.hpp>
#include <rb_tree.hpp>
#include <utils.hpp>
#include <vector>

int main() {
    int count = 20;
    // std::vector<segment_t> segs = Utils::parse_file("input.txt");
    std::vector<segment_t> segs = Utils::TestCaseFactory::grid(1e4, 1e4);
    // std::vector<segment_t> segs = Utils::TestCaseFactory::random(count, 5);
    // std::vector<segment_t> segs = Utils::TestCaseFactory::sparse(count, 10, 5);
    // std::vector<segment_t> segs = Utils::TestCaseFactory::parallelSanted(count);
    // std::vector<segment_t> segs = Utils::TestCaseFactory::drunkGrid(count, 0.1, 10, 2);


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
