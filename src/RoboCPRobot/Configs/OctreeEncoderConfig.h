/*








//WARNING!!!!!!!! This is a template file. Do not change it without necessity.










*/
#pragma once
#include "Config.h"
#include "configFactory.h"

#include "pcl/compression/octree_pointcloud_compression.h"

class OctreeEncoderConfig : public Config{
public:
  OctreeEncoderConfig();
  friend class configFactory;
  ~OctreeEncoderConfig();
#if PCL_VERSION_COMPARE(<, 1, 7, 0)
  pcl::octree::compression_Profiles_e getCompressionProfile();
#else
  pcl::io::compression_Profiles_e getCompressionProfile();
#endif
  bool getShowStatistics();
  double getPointResolution();
  double getOctreeResolution();
  bool getDoVoxelGridDownDownSampling();
  unsigned int getIFrameRate();
  bool getDoColorEncoding();
  unsigned int getColorBitResolution();

private:
#if PCL_VERSION_COMPARE(<, 1, 7, 0)
  pcl::octree::compression_Profiles_e CompressionProfile;
#else
	pcl::io::compression_Profiles_e CompressionProfile;
#endif
  bool ShowStatistics;
  double PointResolution;
  double OctreeResolution;
  bool DoVoxelGridDownDownSampling;
  unsigned int IFrameRate;
  bool DoColorEncoding;
  unsigned int ColorBitResolution;
};