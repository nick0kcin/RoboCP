#pragma once
#include "SenderBase.h"
//#include "KinectData.h"
#include "KinectBuffer.h"
//#include "Config.h"

//#include <boost/asio.hpp>
//#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//#include <pcl/io/pcd_io.h>
//#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include "pcl/compression/octree_pointcloud_compression.h"

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

class Config;

//Class purpose: taking KinectData object from buffer and sending it via TCP-IP
class KinectSender :
  public SenderBase
{
public:
  void Start();

  void Configure(Config* kinectCfg, Config* octreeConfig);
  KinectSender(KinectBuffer * buf);
  ~KinectSender(void);
private:

#if PCL_VERSION_COMPARE(<, 1, 7, 0)
	pcl::octree::PointCloudCompression<pcl::PointXYZ>* octreeCoder;
#else
	pcl::io::OctreePointCloudCompression<pcl::PointXYZ>* octreeCoder;
#endif
 
  KinectBuffer * buffer;
  int port;
};

