#pragma once
#include "ReceivedBuffer.h"
#include "KinectData.h"


class KinectBuffer : public ReceivedBuffer < boost::shared_ptr<KinectData> >
{
public:
  KinectBuffer (int size) : ReceivedBuffer< boost::shared_ptr<KinectData> > (size) {}
};
