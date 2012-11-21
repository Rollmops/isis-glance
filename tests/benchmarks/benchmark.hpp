#ifndef _ISIS_GLANCE_BENCHMAKR_HPP
#define _ISIS_GLANCE_BENCHMARK_HPP

#include <ctime>
#include <iostream>

#define START_TIMER() \
		clock_t timeStart = clock();

#define END_TIMER(TEST_CASE) \
		clock_t timeEnd = clock(); \
		std::cout << "Elapsed time for test case \"" <<  TEST_CASE << \
		"\": " << static_cast<double>(timeEnd - timeStart) \
		/ CLOCKS_PER_SEC * 1000.0 << "ms" << std::endl;

namespace isis {
namespace glance {
namespace benchmark {

typedef uint32_t IterType;
const IterType iterations = std::numeric_limits<IterType>::max();

}
}
}

#endif // _ISIS_GLANCE_BENCHMARK_HPP
