#include <iostream>
#include <line_sweep.hpp>
#include <rb_tree.hpp>
#include <vector>

int main() {
    std::vector<segment_t> segs;
    segs.emplace_back(1, 2, 3, 4);
    segs.emplace_back(2, 3, 4, 5);

#ifdef DEBUG
    std::cout << "Staring Sweep Line Algorithm for: \n";
    for (auto seg : segs) std::cout << seg << "\t";
    std::cout << "\n------------------------------\n";
#endif

    LineSweep sweep(segs);
    sweep.find_intersections();
    auto intersections = sweep.getIntersections();

    for (const auto& intersection : intersections) {
        std::cout << intersection.pt.x << " " << intersection.pt.x << "\n";
    };

    return 0;
}
