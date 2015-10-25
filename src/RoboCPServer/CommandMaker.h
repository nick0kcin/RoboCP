#pragma once
#include <QtCore/qglobal.h>
#include <QtCore/qstring.h>

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

class XMLConfig;

// Class purpose: reading commands from console and sending them to robot
class CommandMaker
{
public:
  void Start ();
  CommandMaker(XMLConfig * x);
  ~CommandMaker(void);
private:
  QString ip;
  quint16 port;
};