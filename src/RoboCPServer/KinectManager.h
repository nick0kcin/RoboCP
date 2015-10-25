#pragma once
#include "KinectBuffer.h"
#include "KinectViewer.h"

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif


// Class purpose: taking KinectData from buffer and giving them to KinectViewer
class KinectManager
{
public:
  void Start ();
  KinectManager(KinectBuffer* b, KinectViewer* v);
  ~KinectManager(void);
private:
  KinectBuffer* kinectBuffer;
  KinectViewer* kinectViewer;
};