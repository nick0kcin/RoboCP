#include "KinectData.h"


KinectData::KinectData(void)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cl (new pcl::PointCloud<pcl::PointXYZ>);
  Cloud = cl;
}

KinectData::KinectData(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, time_t time)
{
  Time = time;
  Cloud = cloud;
}

KinectData::~KinectData(void)
{
}
