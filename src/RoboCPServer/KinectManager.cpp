#pragma once
#include "KinectManager.h"
#include "KinectData.h"


KinectManager::KinectManager (KinectBuffer* b, KinectViewer* v)
{
  kinectBuffer = b;
  kinectViewer = v;
}

KinectManager::~KinectManager ()
{
}

void KinectManager::Start ()
{
#ifdef BOOST
  boost::shared_ptr<KinectData> kData;
#else
  std::shared_ptr<KinectData> kData;
#endif // BOOST
  while (true ) {
	kData = kinectBuffer->Dequeue ();
	kinectViewer->Mtx->lock();
	#ifdef PCL
	  kinectViewer->viewer->updatePointCloud (kData->Cloud, "cloud"); // updating cloud in KinectViewer
#endif
	  // updating CloudTime text line in KinectViewer
	  char buf[50];
	  sprintf (buf, "Cloud time: %s", ctime(&kData->Time) );
	  #ifdef PCL
	  kinectViewer->viewer->updateText (buf, 10, 20, 10, 1, 1, 1, "CloudTime");
	  #endif
	kinectViewer->Mtx->unlock();
  }
}
