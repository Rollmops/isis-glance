#include "benchmark.hpp"
#include <util/orientation.hpp>
#include <iostream>

isis::glance::util::Orientation orientation;
bool isLatched;

DEFINE_BENCHMARK(test1)
{
	isLatched = orientation.isLatched();
}


RUN_BENCHMARKS()
