#pragma once
#include "joystickData.h"
#include "QtCore\qthread.h"
#include "QtCore\qstring.h"
#include "QtCore\qelapsedtimer.h"
#include "com_connection.h"
#include "robotLink.h"

class JoystickThread : public QThread
{
	JoystickData data;
	Joystick* joystick;
	MavlinkBuffer* buffer;
	const int cJoystickRate = 59;
public:
	JoystickThread(Joystick* joystick, MavlinkBuffer* buffer);
	// overriding the QThread's run() method
	void run();	
};

class RobotLinkThread : public QThread{
	MavlinkBuffer* buffer;
	RobotLinker* link;
	MavlinkPacket packet;
	MavlinkVisitor* visitor;
public:
	RobotLinkThread(MavlinkBuffer* buffer, RobotLinker* link, MavlinkVisitor* visitor);

	void run();

	void sleep_m(int millis);
};
