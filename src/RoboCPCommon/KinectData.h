#pragma once
#include <time.h>
#ifdef PCL
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#else
#endif

class KinectData
{
public:
#ifdef PCL
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW  // Dont know if actually need it
  pcl::PointCloud<pcl::PointXYZ>::Ptr Cloud; // Boost shared_ptr to point cloud
  #else
  #endif
  time_t Time; // Time
  KinectData(void);
  #ifdef PCL
  KinectData(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, time_t time);
  #else
  #endif
  ~KinectData();
};
