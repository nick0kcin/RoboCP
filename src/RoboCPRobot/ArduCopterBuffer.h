#pragma once
#include "ReceivedBuffer.h"
#include "ArduCopterReceived.h"

#ifdef BOOST
class ArduCopterBuffer : public ReceivedBuffer < boost::shared_ptr<ArduCopterReceived> >
{
public:
	ArduCopterBuffer (int size) : ReceivedBuffer < boost::shared_ptr<ArduCopterReceived> > (size) {}
};
#else
class ArduCopterBuffer : public ReceivedBuffer < std::shared_ptr<ArduCopterReceived> >
{
public:
	ArduCopterBuffer (int size) : ReceivedBuffer < std::shared_ptr<ArduCopterReceived> > (size) {}
};
#endif
