#pragma once
#include "ReceivedBuffer.h"
#include "Send.h"

class SendBuffer : public ReceivedBuffer < boost::shared_ptr<Send> >
{
public:
	SendBuffer (int size) : ReceivedBuffer< boost::shared_ptr<Send> > (size) {}
};

