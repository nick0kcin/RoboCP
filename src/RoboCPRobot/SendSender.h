#pragma once
#include "SenderBase.h"
#include "SendBuffer.h"

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

class Config;

//Class purpose: taking Send object from buffer and sending it via TCP-IP
class SendSender :
  public SenderBase
{
public:
  void Start(); 

  SendSender(SendBuffer * buf);
  void Configure(Config* sendConfig);
  ~SendSender(void);
private:
  SendBuffer * buffer;
  int port;
};

