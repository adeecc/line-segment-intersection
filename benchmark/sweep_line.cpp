#include <benchmark/benchmark.h>

#include <iostream>
#include <line_sweep.hpp>
#include <utils.hpp>

static void BM_SweepLineGrid(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();

        state.SetComplexityN(state.range(0) + state.range(1));

        std::vector<segment_t> segs = Utils::TestCaseFactory::grid(state.range(0), state.range(1));
        LineSweep sweep(segs);

        state.ResumeTiming();

        sweep.find_intersections();
    }
}

static void BM_SweepLineRandom(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();

        state.SetComplexityN(state.range(0));

        std::vector<segment_t> segs = Utils::TestCaseFactory::random(state.range(0), 100);
        LineSweep sweep(segs);

        state.ResumeTiming();

        sweep.find_intersections();
    }
}

BENCHMARK(BM_SweepLineGrid)
    ->ArgsProduct({benchmark::CreateRange(1, 1 << 14, 1 << 4),
                   benchmark::CreateRange(1, 1 << 14, 1 << 4)})
    ->Complexity();

BENCHMARK(BM_SweepLineRandom)
    ->ArgsProduct({benchmark::CreateRange(1, 1 << 10, 2)})
    ->Complexity();

BENCHMARK_MAIN();