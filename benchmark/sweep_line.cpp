#include <benchmark/benchmark.h>

#include <cmath>
#include <iostream>
#include <line_sweep.hpp>
#include <utils.hpp>

static void BM_SweepLineGrid(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();

        double n = state.range(0) + state.range(1);
        double k = state.range(0) + state.range(1);

        state.SetComplexityN((n + k) * log10(n));

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

        std::vector<segment_t> segs = Utils::TestCaseFactory::random(state.range(0), 5);
        LineSweep sweep(segs);

        state.ResumeTiming();

        sweep.find_intersections();
    }
}

BENCHMARK(BM_SweepLineGrid)
    ->ArgsProduct({benchmark::CreateDenseRange(1e4, 2e4, 100), {100}})
    ->Complexity();

BENCHMARK(BM_SweepLineGrid)
    ->ArgsProduct({benchmark::CreateRange(1, 1 << 14, 1 << 2),
                   benchmark::CreateRange(1, 1 << 14, 1 << 2)})
    ->Complexity();

// BENCHMARK(BM_SweepLineRandom)
//     ->ArgsProduct({benchmark::CreateRange(1, 1 << 10, 2)})
//     ->Complexity();

BENCHMARK_MAIN();