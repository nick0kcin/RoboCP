#pragma once
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

class XMLConfig;

// Class purpose: showing point cloud and other info
class KinectViewer
{
public:
  void Start ();
  KinectViewer(XMLConfig * x);
  ~KinectViewer(void);
  boost::interprocess::interprocess_mutex* Mtx; // Mutex for thread safety
  pcl::visualization::PCLVisualizer* viewer;
};