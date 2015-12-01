#pragma once
#include "SendBuffer.h"
#include "KinectViewer.h"

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif


enum ArduCopterReceivedType{
  AccelerationPacket,
  AnglesPacket,
  AltitudePacket
};

// Class purpose: taking Send objects from buffer and updating KinectViewer info
class SendManager
{
public:
  void Start ();
  SendManager (SendBuffer* b, KinectViewer* v);
  ~SendManager (void);
private:
  SendBuffer* sendBuffer;
  KinectViewer* kinectViewer;
  #ifdef BOOST
  void updateText (boost::shared_ptr<Send> s);
  #else
  void updateText (std::shared_ptr<Send> s);
  #endif
};
