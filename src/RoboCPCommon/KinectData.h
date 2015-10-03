#pragma once
#include <time.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


class KinectData
{
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW  // Dont know if actually need it
  pcl::PointCloud<pcl::PointXYZ>::Ptr Cloud; // Boost shared_ptr to point cloud
  time_t Time; // Time
  KinectData(void);
  KinectData(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, time_t time);
  ~KinectData();
};