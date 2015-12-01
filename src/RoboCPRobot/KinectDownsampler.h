#pragma once
#include "KinectBuffer.h"
#ifdef PCL
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#endif // PCL

// Class purpose: downsampling point clouds from 640x480 to 64x48
class KinectDownsampler
{
public:
  void Start ();
  KinectDownsampler(KinectBuffer * inputBuf, KinectBuffer * outputBuf);
  ~KinectDownsampler(void);
private:
  KinectBuffer * inputBuffer;
  KinectBuffer * outputBuffer;
  #ifdef PCL
  void downsample (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &CloudIn, pcl::PointCloud<pcl::PointXYZ>::Ptr &CloudOut);
  #endif
};

