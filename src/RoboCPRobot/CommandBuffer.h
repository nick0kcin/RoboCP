#pragma once
#include "ReceivedBuffer.h"
#include "Command.h"
#ifdef BOOST
class CommandBuffer :  public ReceivedBuffer <boost::shared_ptr<Command> >
{
public:
  CommandBuffer (int size) : ReceivedBuffer <boost::shared_ptr<Command> > (size) {}
};
#else
class CommandBuffer :  public ReceivedBuffer <std::shared_ptr<Command> >
{
public:
  CommandBuffer (int size) : ReceivedBuffer <std::shared_ptr<Command> > (size) {}
};
#endif
