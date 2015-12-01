#pragma once
#include <QtCore/qglobal.h>
#include <QtCore/qstring.h>
#include "SendBuffer.h"
#include <iostream>
#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

class XMLConfig;

// Class purpose: receivig Send objects and adding them to buffer
class SendReceiver
{
public:
  void Start ();
  SendReceiver (XMLConfig * x, SendBuffer* b);
  ~SendReceiver (void);
private:
  QString ip;
  quint16 port;
  SendBuffer* sendBuffer;
};
