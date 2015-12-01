#include <iostream>
#ifdef PCL
#include <pcl/io/openni2_grabber.h>
#include <pcl/io/pcd_io.h>
#endif // PCL
#ifdef BOOST
#include <boost/bind.hpp>
#else
#include <functional>
#endif
#include "KinectController.h"
#include "KinectData.h"

KinectController::KinectController(KinectBuffer * buf)
{
  buffer = buf;
}
#ifdef PCL
void KinectController::grabberCallBack (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
{

  pcl::PointCloud<pcl::PointXYZ>::Ptr cld (new pcl::PointCloud<pcl::PointXYZ> (*cloud) );
  boost::shared_ptr<KinectData> kData (new KinectData (cld, time(NULL) ) ); // Creating KinectData
  buffer->Enqueue (kData); // Adding it to buffer
}
#endif
void KinectController::Start(void)
{
#ifdef PCL
  pcl::Grabber* interface = new pcl::io::OpenNI2Grabber (); // Creating new grabber
#ifdef BOOST
  boost::function<void
  (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f = boost::bind (&KinectController::grabberCallBack, this, _1);
#else
  std::function<void
  (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f = std::bind (&KinectController::grabberCallBack, this, _1);

#endif // BOOST
  boost::signals2::connection c = interface->registerCallback (f);
  interface->start ();
  #endif
}

KinectController::~KinectController()
{
}

void KinectController::FakeStart ()
{
  std::cout << "KinectController: loading clouds..." << std::endl; //TODO: write in log
  #ifdef ENABLE_LOGGING
  RAW_LOG (INFO, "KinectController: loading clouds...!");
  #endif
#ifdef PCL
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::io::loadPCDFile<pcl::PointXYZ> ("KinectCloud1.pcd", *cloud1 ); // loading clouds from HDD
  pcl::io::loadPCDFile<pcl::PointXYZ> ("KinectCloud2.pcd", *cloud2 );
  std::cout << "KinectController: ready" << std::endl; //TODO: write in log
  #ifdef ENABLE_LOGGING
  RAW_LOG (INFO, "KinectController: ready");
  #endif
  while (true) { // Making new KinectData every 2 seconds
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	boost::shared_ptr<KinectData> kData1 (new KinectData (cloud1, time(NULL) ) );
	buffer->Enqueue (kData1);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	boost::shared_ptr<KinectData> kData2 (new KinectData (cloud2, time(NULL) ) );
	buffer->Enqueue (kData2);
  }
  #else
 std::cout<<"NO PCL"<<std::endl;
 while(true)
 {

 std::this_thread::sleep_for(std::chrono::milliseconds(100));
 std::shared_ptr<KinectData> kData1 (new KinectData () );
 buffer->Enqueue(kData1);

 std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::shared_ptr<KinectData> kData2 (new KinectData () );
 buffer->Enqueue(kData2);
 }
  #endif // PCL
}
