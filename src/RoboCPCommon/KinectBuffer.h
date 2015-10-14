#pragma once
#include "ReceivedBuffer.h"

class KinectData;

class KinectBuffer : public ReceivedBuffer < boost::shared_ptr<KinectData> >
{
public:
  KinectBuffer (int size) : ReceivedBuffer< boost::shared_ptr<KinectData> > (size) {}
};
