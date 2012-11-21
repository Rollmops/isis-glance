#include "benchmark.hpp"
#include <util/orientation.hpp>

int main()
{
	using namespace isis::glance::benchmark;
	isis::glance::util::Orientation orientation;
	bool isLatched;
	START_TIMER()
	for( IterType i = 0; i<iterations; ++i ) {
		isLatched = orientation.isLatched();
	}
	END_TIMER("isis::glance::Orientation::isLatched()")
	return 0;
}
