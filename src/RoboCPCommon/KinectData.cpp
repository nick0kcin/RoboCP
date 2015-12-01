#include "KinectData.h"

KinectData::KinectData(void)
{
#ifdef PCL
  pcl::PointCloud<pcl::PointXYZ>::Ptr cl (new pcl::PointCloud<pcl::PointXYZ>);
  Cloud = cl;
  #else
  Time=time(NULL);
  #endif
}
#ifdef PCL
KinectData::KinectData(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, time_t time)
{
  Time = time;
  Cloud = cloud;
}
#else
#endif
KinectData::~KinectData(void)
{
}
