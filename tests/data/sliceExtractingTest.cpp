#define BOOST_TEST_MODULE SliceExtractingTest
#include <boost/test/unit_test.hpp>
#include <data/image.hpp>
#include <data/slice.hpp>

namespace isis
{
namespace glance
{
namespace test
{

template<typename T>
isis::glance::data::Volume createVolume( size_t row, size_t column, size_t slice, isis::data::dimensions dim )
{
	isis::data::MemChunk<T> chunk( row, column, slice );

	for( size_t z = 0; z < slice; z++ ) {
		for( size_t y = 0; y < column; y++ ) {
			for( size_t x = 0; x < row; x++ ) {
				const isis::util::ivector4 coords( x, y, z );
				static_cast<isis::data::Chunk &>( chunk ).voxel<T>( x, y, z ) = coords[dim];
			}
		}
	}

	const size_t size[] =  { row, column, slice };

	return isis::glance::data::Volume( static_cast<isis::data::Chunk &>( chunk ).asValueArrayBase(), size );

}

template<typename T>
bool checkSlice( isis::glance::data::Slice slice )
{
	isis::glance::data::Slice::size_type size ( slice.getSizeAsVector()[0], slice.getSizeAsVector()[1] );

	for( size_t y = 0; y < size[1]; y++ ) {
		for( size_t x = 0; x < size[0]; x++ ) {
			const size_t dims[] = {x, y};

			if( slice.voxel<T>( dims ) != static_cast<T>( x ) ) {
				return false;
			}
		}
	}

	return true;
}


}
}
}