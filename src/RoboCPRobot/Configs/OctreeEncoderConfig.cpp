/*








//WARNING!!!!!!!! This is a template file. Do not change it without necessity.










*/

#include "OctreeEncoderConfig.h"

OctreeEncoderConfig::OctreeEncoderConfig() :
#ifdef PCL
CompressionProfile(),
#endif
 ShowStatistics(false), PointResolution(0.0), OctreeResolution(0.0), DoVoxelGridDownDownSampling(false), IFrameRate(), DoColorEncoding(false), ColorBitResolution()
{

}
OctreeEncoderConfig::~OctreeEncoderConfig()
{

}
#ifdef PCL
#if PCL_VERSION_COMPARE(<, 1, 7, 0)
pcl::octree::compression_Profiles_e OctreeEncoderConfig::getCompressionProfile()
{
#else
pcl::io::compression_Profiles_e OctreeEncoderConfig::getCompressionProfile()
#endif
{
	return CompressionProfile;
}
#endif
bool OctreeEncoderConfig::getShowStatistics()
{
	return ShowStatistics;
}
double OctreeEncoderConfig::getPointResolution()
{
	return PointResolution;
}
double OctreeEncoderConfig::getOctreeResolution()
{
	return OctreeResolution;
}
bool OctreeEncoderConfig::getDoVoxelGridDownDownSampling()
{
	return DoVoxelGridDownDownSampling;
}
unsigned int OctreeEncoderConfig::getIFrameRate()
{
	return IFrameRate;
}
bool OctreeEncoderConfig::getDoColorEncoding()
{
	return DoColorEncoding;
}
unsigned int OctreeEncoderConfig::getColorBitResolution()
{
	return ColorBitResolution;
}
