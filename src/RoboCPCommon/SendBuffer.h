#pragma once
#include "ReceivedBuffer.h"
#include "Send.h"

#ifdef BOOST
class SendBuffer : public ReceivedBuffer < boost::shared_ptr<Send> >
{
public:
	SendBuffer (int size) : ReceivedBuffer< boost::shared_ptr<Send> > (size) {}
};
#else
class SendBuffer : public ReceivedBuffer < std::shared_ptr<Send> >
{
public:
	SendBuffer (int size) : ReceivedBuffer< std::shared_ptr<Send> > (size) {}
};
#endif // BOOST

