#pragma once
#include <QtCore/qglobal.h>
#include "Config.h"
#include "Command.h"

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

// Class purpose: Receiving commands from server
class ClientReceiver
{
public:
	void Start();
	ClientReceiver();
	void Configure(Config * commandConfig);
	~ClientReceiver(void);
private:
	quint16 port;
};

