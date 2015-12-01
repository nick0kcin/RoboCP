#pragma once
#include "ReceivedBuffer.h"
#include "CameraReceived.h"

#ifdef BOOST
class CameraReceivedBuffer :  public ReceivedBuffer <boost::shared_ptr<CameraReceived>>
{
public:
  CameraReceivedBuffer (int size) : ReceivedBuffer <boost::shared_ptr<CameraReceived>> (size) {}
};
#else
class CameraReceivedBuffer :  public ReceivedBuffer <std::shared_ptr<CameraReceived>>
{
public:
  CameraReceivedBuffer (int size) : ReceivedBuffer <std::shared_ptr<CameraReceived>> (size) {}
};
#endif

