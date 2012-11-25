#include "benchmark.hpp"
#include <util/orientation.hpp>
#include <iostream>

using namespace isis::glance::benchmark;

isis::glance::util::Orientation orientation;
bool isLatched = false;

DEFINE_BENCHMARK(isis_glance_util_Orienation_isLatched)
{
	for( IterationsType i = 0; i < numberIterations; ++i ) {
		isLatched = !orientation.isLatched();
	}
}


RUN_BENCHMARKS()
