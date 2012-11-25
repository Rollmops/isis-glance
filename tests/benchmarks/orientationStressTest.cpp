#include "benchmark.hpp"
#include <util/orientation.hpp>
#include <iostream>

using namespace isis::glance::benchmark;

isis::glance::util::Orientation orientation;
bool isLatched = false;

DEFINE_BENCHMARK(isis_glance_util_Orienation_isLatched)
{
	LOOP() {
		isLatched = !orientation.isLatched();
	}
}

DEFINE_BENCHMARK(isis_glance_util_orientation_rotate)
{
	LOOP() {
		orientation.rotate(45.0f,45.0f,45.0f);
	}

}

RUN_BENCHMARKS()
