#pragma once
#include "KinectBuffer.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


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
  void downsample (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &CloudIn, pcl::PointCloud<pcl::PointXYZ>::Ptr &CloudOut);
};

