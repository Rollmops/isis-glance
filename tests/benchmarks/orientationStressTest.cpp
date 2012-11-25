#include "benchmark.hpp"
#include <util/orientation.hpp>
#include <iostream>

isis::glance::util::Orientation orientation;

DEFINE_BENCHMARK(test1)
{
	orientation.isLatched();
}


RUN_BENCHMARKS()
