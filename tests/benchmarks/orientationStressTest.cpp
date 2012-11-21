#include "time.hpp"
#include <util/orientation.hpp>

#define ITERATIONS 300000

int main()
{
	isis::glance::util::Orientation orientation;
	bool isLatched;
	START_TIMER()
	for( uint32_t i = 0; i<ITERATIONS; ++i ) {
		isLatched = orientation.isLatched();
	}
	END_TIMER("isis::glance::Orientation::isLatched()")
	return 0;
}
