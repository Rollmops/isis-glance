#define BOOST_TEST_MODULE OrienationTest

#include <boost/test/unit_test.hpp>
#include <util/orientation.hpp>

namespace isis {
namespace glance {
namespace test {

BOOST_AUTO_TEST_CASE( orientation_test ) {

	util::Orientation orientationAxial( util::Orientation::AXIAL );
	util::Orientation orientationSagittal( util::Orientation::SAGITTAL );
	util::Orientation orientationCoronal( util::Orientation::CORONAL );

	BOOST_CHECK(orientationAxial.is( util::Orientation::AXIAL) );
	BOOST_CHECK(orientationSagittal.is( util::Orientation::SAGITTAL) );
	BOOST_CHECK(orientationCoronal.is( util::Orientation::CORONAL) );

	BOOST_CHECK(!orientationAxial.is(util::Orientation::SAGITTAL)); // NOT
	BOOST_CHECK(!orientationAxial.is(util::Orientation::CORONAL)); // NOT

	BOOST_CHECK(!orientationSagittal.is(util::Orientation::CORONAL)); // NOT
	BOOST_CHECK(!orientationSagittal.is(util::Orientation::AXIAL)); // NOT

	BOOST_CHECK(!orientationCoronal.is(util::Orientation::SAGITTAL)); // NOT
	BOOST_CHECK(!orientationCoronal.is(util::Orientation::AXIAL)); // NOT




}

}
}
}
