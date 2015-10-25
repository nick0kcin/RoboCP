#pragma once
#include "KinectBuffer.h"
#include "pcl/compression/octree_pointcloud_compression.h"
#include <QtCore/qstring.h>
#include <QtCore/qglobal.h>

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

class XMLConfig;

// Class purpose: receiving KinectData from robot and giving them to KinectBuffer
class KinectReceiver
{
public:
  void Start ();
  KinectReceiver(XMLConfig * x, KinectBuffer* b);
  ~KinectReceiver(void);
private:
  KinectBuffer* kinectBuffer;
  #if PCL_VERSION_COMPARE(<, 1, 7, 0)
  pcl::octree::PointCloudCompression<pcl::PointXYZ>* octreeCoder;
  #else
  pcl::io::OctreePointCloudCompression<pcl::PointXYZ>* octreeCoder;
  #endif
  QString ip;
  quint16 port;
};