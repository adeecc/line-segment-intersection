#pragma once

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <line_segment.hpp>
#include <random>
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
            stream << seg.u.x << " " << seg.u.y << " " << seg.v.x << " " << seg.v.y << "\n";
        }

        stream << intersections.size() << "\n";
        for (const point_t& its : intersections) {
            stream << its.x << " " << its.y << "\n";
        }

        stream.close();
    }

    class TestCaseFactory {
       private:
        struct LineSet {
            double x_base_bot, x_base_top;
            double y_bot, y_top;

            double del;

            LineSet(double x_base_bot, double x_base_top, double y_bot, double y_top, double del) : x_base_bot(x_base_bot),
                                                                                                    x_base_top(x_base_top),
                                                                                                    y_bot(y_bot),
                                                                                                    y_top(y_top),
                                                                                                    del(del) {}

            segment_t generate_point(int i) {
                return {x_base_bot + i * del, y_bot, x_base_top + i * del, y_top};
            }
        };

       public:
        static std::vector<segment_t> grid(int m, int n) {
            std::array<LineSet, 2> line_set{LineSet(0, 5, 0, 8, 4.5), LineSet(1.5, -10, 0, 8, 6)};

            std::vector<segment_t> segs;
            segs.reserve(m * n);

            for (int i = 0; i < m; ++i) {
                auto seg = line_set[0].generate_point(i);
                segs.push_back(seg);
            }

            for (int i = 0; i < n; ++i) {
                auto seg = line_set[1].generate_point(i);
                segs.push_back(seg);
            }

            return segs;
        }

        static std::vector<segment_t> random(int count, double range) {
            std::random_device dev;
            std::default_random_engine gen(dev());

            std::uniform_real_distribution<double> dist(-range, range);

            std::vector<segment_t> segs;
            segs.reserve(count);

            for (int i = 0; i < count; ++i) {
                segs.emplace_back(dist(gen), dist(gen), dist(gen), dist(gen));
            }

            return segs;
        }

        static std::vector<segment_t> sparse(int count, double mean, double std) {
            std::random_device dev;
            std::default_random_engine gen(dev());
            std::normal_distribution<double> dist(mean, std);

            std::vector<segment_t> segs;
            segs.reserve(count);

            for (int i = 0; i < count; ++i) {
                for (int j = 0; j < count; ++j) {
                    double x_1 = i * 10;
                    double y_1 = j * 10;
                    double GAUSSIAN_PARAM = dist(gen);

                    double x_2 = x_1 + 10 * std::cos(GAUSSIAN_PARAM);
                    double y_2 = y_1 + 10 * std::sin(GAUSSIAN_PARAM);

                    segs.emplace_back(x_1, y_1, x_2, y_2);
                }
            }
            return segs;
        }

        static std::vector<segment_t> parallelSanted(int count) {
            std::vector<segment_t> segs;
            segs.reserve(count);

            for (int i = 0; i < count; ++i) {
                double x_1 = -i;
                double y_1 = i;

                double x_2 = i;
                double y_2 = i + 1;

                segs.emplace_back(x_1, y_1, x_2, y_2);
            }

            return segs;
        }

        static std::vector<segment_t> drunkGrid(int count, double variance, double mean, double std) {
            std::random_device dev;
            std::default_random_engine gen(dev());
            std::normal_distribution<double> dist(mean, std);

            std::vector<segment_t> segs;
            segs.reserve(2 * count);

            double dx = 0, dy = -0.3;
            for (int i = 0; i < count; ++i) {
                double x_1 = dx + dist(gen) * variance;
                double y_1 = dy + i + dist(gen) * variance;

                double x_2 = dx + (count - 1) + dist(gen) * variance;
                double y_2 = dy + i + dist(gen) * variance;

                segs.emplace_back(x_1, y_1, x_2, y_2);

                x_1 = dx + i + dist(gen) * variance;
                y_1 = dy + dist(gen) * variance;

                x_2 = dx + i + dist(gen) * variance;
                y_2 = dy + (count - 1) + dist(gen) * variance;

                segs.emplace_back(x_1, y_1, x_2, y_2);
            }
            return segs;
        }

        static std::vector<segment_t> cube(int count, double dPi = 30, double radius = 4) {
            double dAngle = M_PI / dPi;

            std::vector<segment_t> segs;
            segs.reserve(4 * count);

            double angle = 0;
            for (int i = 0; i < count; ++i) {
                angle += dAngle;

                double x = std::cos(angle) * radius;
                double y = std::sin(angle) * radius;

                radius *= 1.04;

                segs.emplace_back(x, y, -y, x);
                segs.emplace_back(-y, x, -x, -y);
                segs.emplace_back(-x, -y, y, -x);
                segs.emplace_back(y, -x, x, y);
            }

            return segs;
        }
    };

}  // namespace Utils