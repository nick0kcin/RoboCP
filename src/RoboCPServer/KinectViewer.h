#pragma once
#ifdef PCL
#include <pcl/visualization/pcl_visualizer.h>
#endif
#ifdef BOOST
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#else
#include <mutex>
#include <thread>
#endif
class XMLConfig;

// Class purpose: showing point cloud and other info
class KinectViewer
{
public:
  void Start ();
  KinectViewer(XMLConfig * x);
  ~KinectViewer(void);
  #ifdef BOOST
  boost::interprocess::interprocess_mutex* Mtx; // Mutex for thread safety
  #else
  std::mutex * Mtx;
  #endif
#ifdef PCL
  pcl::visualization::PCLVisualizer* viewer;
#endif // PCL
};
