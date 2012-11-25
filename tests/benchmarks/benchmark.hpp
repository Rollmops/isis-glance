#ifndef _ISIS_GLANCE_BENCHMAKR_HPP
#define _ISIS_GLANCE_BENCHMARK_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <list>
#include <boost/foreach.hpp>




#define START_TIMER() 																\
		clock_t timeStart = clock();

#define END_TIMER(TEST_CASE) 														\
		clock_t timeEnd = clock(); 													\
		std::cout << "Elapsed time for benchmark \"" <<  TEST_CASE << 				\
		"\": " << static_cast<double>(timeEnd - timeStart) 							\
		/ CLOCKS_PER_SEC * 1000.0 << "ms" << std::endl;


namespace isis {
namespace glance {
namespace benchmark {

typedef uint32_t IterationsType;
const IterationsType numberIterations = 80000;

namespace _internal {

void checkDebug() {
//warn if user builds in debug mode
#ifndef NDEBUG
	std::cout << "Benchmark tests are built in debug mode! " <<
			"This will affect your benchmark results! " << std::endl;
#endif
}

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
#define DEFINE_BENCHMARK(NAME) 														\
	class Benchmark_ ##NAME 														\
	: public isis::glance::benchmark::_internal::BenchmarkBase { 					\
	public: 																		\
		Benchmark_ ##NAME() { 														\
			isis::glance::benchmark::_internal::benchmarkList.push_back( this );	\
			name = std::string( "" #NAME "");										\
		} 																			\
		virtual void operator()() const; 											\
	}; 																				\
	static const Benchmark_ ##NAME  _instance_ ##NAME; 								\
	void Benchmark_ ##NAME ::operator() () const


#define RUN_BENCHMARKS() 															\
	int main() { 																	\
	using namespace isis::glance::benchmark; 										\
	_internal::checkDebug();														\
	typedef std::list<_internal::BenchmarkBase*> ListType;							\
	BOOST_FOREACH( ListType::const_reference ref, _internal::benchmarkList) 		\
	{ 																				\
		START_TIMER() 																\
			ref->operator()(); 														\
		END_TIMER(ref->name) 														\
	}																				\
	return 0; }


#endif // _ISIS_GLANCE_BENCHMARK_HPP
