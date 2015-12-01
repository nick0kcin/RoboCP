#pragma once
#include "ReceivedBuffer.h"
#include "NanoReceived.h"

#ifdef BOOST
class NanoReceivedBuffer :
  public ReceivedBuffer< boost::shared_ptr<NanoReceived> >
{
public:
	NanoReceivedBuffer (int size) : ReceivedBuffer< boost::shared_ptr<NanoReceived> > (size) {}
};
#else
class NanoReceivedBuffer :
  public ReceivedBuffer< std::shared_ptr<NanoReceived> >
{
public:
	NanoReceivedBuffer (int size) : ReceivedBuffer< std::shared_ptr<NanoReceived> > (size) {}
};
#endif

