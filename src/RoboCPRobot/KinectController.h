#pragma once
#include "Controller.h"
#include "KinectBuffer.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <thread>
#include <chrono>

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

// Kinect grabber in details: http://www.pointclouds.org/documentation/tutorials/openni_grabber.php#openni-grabber

// Class purpose: getting point clouds from kinect, creating KinectData objects and placing them to buffer
class KinectController :
  public Controller
{
public:
  void Start ();
  void FakeStart (); // For testing with no kinect

  KinectController(KinectBuffer * buf);
  ~KinectController(void);
private:
  KinectBuffer * buffer;
  void grabberCallBack (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud); // CallBack function for grabber
};

