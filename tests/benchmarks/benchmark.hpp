#ifndef _ISIS_GLANCE_BENCHMAKR_HPP
#define _ISIS_GLANCE_BENCHMARK_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <list>
#include <boost/foreach.hpp>

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

typedef uint16_t IterType;
const IterType iterations = std::numeric_limits<IterType>::max();

namespace _internal {
class BenchmarkBase {
public:
	virtual void operator ()() const = 0;
	virtual ~BenchmarkBase() {}
	std::string name;
};

std::list<BenchmarkBase*> benchmarkList;

} // end namespace _internal
}
}
}
#define DEFINE_BENCHMARK(NAME) \
	class Benchmark_ ##NAME \
	: public isis::glance::benchmark::_internal::BenchmarkBase { \
	public: \
		Benchmark_ ##NAME() { \
			isis::glance::benchmark::_internal::benchmarkList.push_back( this ); \
			name = std::string( "" #NAME "");\
		} \
		virtual void operator()() const; \
	}; \
	static const Benchmark_ ##NAME  _instance_ ##NAME; \
	void Benchmark_ ##NAME ::operator() () const


#define RUN_BENCHMARKS() \
	int main() { \
	using namespace isis::glance::benchmark; \
	typedef std::list<_internal::BenchmarkBase*> ListType; \
	BOOST_FOREACH( ListType::const_reference ref, _internal::benchmarkList) \
	{ \
		START_TIMER() \
		for( IterType i = 0; i < iterations; ++i) { \
			ref->operator()(); \
		}\
		END_TIMER(ref->name) \
	}\
	return 0; }


#endif // _ISIS_GLANCE_BENCHMARK_HPP
