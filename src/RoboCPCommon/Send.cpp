#include "Send.h"
#include "QtCore/qdatastream.h"

Send::Send(void)
{
}


Send::~Send(void)
{
}

QDataStream& operator<<(QDataStream& out, const Send& send)
{
	out << send.TopSonicSensor << send.FrontSonicSensor << send.LeftSonicSensor << send.RightSonicSensor << send.BackSonicSensor;
	out << send.Roll << send.Pitch << send.Yaw << send.AltitudeSonic << send.AltitudeBarometer;
	out << send.Acceleration.x << send.Acceleration.y << send.Acceleration.z;
	out << send.PacketType;
	struct std::tm tm;
    gmtime_r(&send.Time,&tm);
      char timestr[9];
	  sprintf(timestr,"%d:%d:%d",tm.tm_hour,tm.tm_min,tm.tm_sec);
	out <<QString(timestr) ;
	out << send.Motion.BeginningX << send.Motion.BeginningY << send.Motion.EndX << send.Motion.EndY << send.Motion.Length;
	return out;
}

QDataStream& operator>>(QDataStream& in, Send& send)
{
	in >> send.TopSonicSensor >> send.FrontSonicSensor >> send.LeftSonicSensor >> send.RightSonicSensor >> send.BackSonicSensor;
	in >> send.Roll >> send.Pitch >> send.Yaw >> send.AltitudeSonic >> send.AltitudeBarometer;
	in >> send.Acceleration.x >> send.Acceleration.y >> send.Acceleration.z;
	in >> send.PacketType;
	QString TimeString;
	in >> TimeString;
	  struct std::tm tm;
	  sscanf(TimeString.toStdString().c_str(),"%d:%d:%d",&tm.tm_hour,&tm.tm_min,&tm.tm_sec);
	  send.Time=mktime(&tm);
	in >> send.Motion.BeginningX >> send.Motion.BeginningY >> send.Motion.EndX >> send.Motion.EndY >> send.Motion.Length;
	return in;
}
