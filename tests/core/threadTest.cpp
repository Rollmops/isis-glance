#include <iostream>
#include <stdio.h>

#include "util/thread.hpp"


const size_t counter = 999000;

class MyThread1 : public isis::glance::util::Thread
{
	float *sharedData_;
public:
	MyThread1( ){}
	void setSharedData( float* sD ) { sharedData_ = sD; }
	virtual void run() {
		for( size_t i = 0; i < counter; i++ ) {
			if( sharedData_[i] == 0 ) {
				sharedData_[i]++;
			}
		}
	};

};


int main(  )
{
	boost::scoped_array<float> sharedData(new float[counter]);
	for( size_t i = 0; i < counter; i++ ) {
		sharedData[i] = 0;
	}

	


	for( size_t i = 0; i < counter; i++ ) {
		if( sharedData[i] > 1 ) {
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
	return 0;
}
