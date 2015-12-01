#pragma once
#include "ReceivedBuffer.h"

class KinectData;

#ifdef BOOST
class KinectBuffer : public ReceivedBuffer < boost::shared_ptr<KinectData> >
{
public:
  KinectBuffer (int size) : ReceivedBuffer< boost::shared_ptr<KinectData> > (size) {}
};
#else
class KinectBuffer : public ReceivedBuffer < std::shared_ptr<KinectData> >
{
public:
  KinectBuffer (int size) : ReceivedBuffer< std::shared_ptr<KinectData> > (size) {}
};
#endif
