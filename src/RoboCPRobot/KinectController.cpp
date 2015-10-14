#include <iostream>
#include <pcl/io/openni2_grabber.h>
#include <pcl/io/pcd_io.h>
#include <boost/bind.hpp>
#include "KinectController.h"
#include "KinectData.h"

KinectController::KinectController(KinectBuffer * buf)
{
  buffer = buf;
}

void KinectController::grabberCallBack (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cld (new pcl::PointCloud<pcl::PointXYZ> (*cloud) );
  boost::shared_ptr<KinectData> kData (new KinectData (cld, time(NULL) ) ); // Creating KinectData
  buffer->Enqueue (kData); // Adding it to buffer
}

void KinectController::Start(void)
{
  pcl::Grabber* interface = new pcl::io::OpenNI2Grabber (); // Creating new grabber

  boost::function<void
  (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f = boost::bind (&KinectController::grabberCallBack, this, _1);

  boost::signals2::connection c = interface->registerCallback (f);

  interface->start ();
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

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::io::loadPCDFile<pcl::PointXYZ> ("KinectCloud1.pcd", *cloud1 ); // loading clouds from HDD
  pcl::io::loadPCDFile<pcl::PointXYZ> ("KinectCloud2.pcd", *cloud2 );
  std::cout << "KinectController: ready" << std::endl; //TODO: write in log
  #ifdef ENABLE_LOGGING
  RAW_LOG (INFO, "KinectController: ready");
  #endif
  while (true) { // Making new KinectData every 2 seconds
	Sleep (100);
	boost::shared_ptr<KinectData> kData1 (new KinectData (cloud1, time(NULL) ) );
	buffer->Enqueue (kData1);

	Sleep (100);
	boost::shared_ptr<KinectData> kData2 (new KinectData (cloud2, time(NULL) ) );
	buffer->Enqueue (kData2);
  }
}