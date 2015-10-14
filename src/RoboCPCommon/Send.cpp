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
	out << send.Time;
	out << send.Motion.BeginningX << send.Motion.BeginningY << send.Motion.EndX << send.Motion.EndY << send.Motion.Length;
	return out;
}

QDataStream& operator>>(QDataStream& in, Send& send)
{
	in >> send.TopSonicSensor >> send.FrontSonicSensor >> send.LeftSonicSensor >> send.RightSonicSensor >> send.BackSonicSensor;
	in >> send.Roll >> send.Pitch >> send.Yaw >> send.AltitudeSonic >> send.AltitudeBarometer;
	in >> send.Acceleration.x >> send.Acceleration.y >> send.Acceleration.z;
	in >> send.PacketType;
	in >> send.Time;
	in >> send.Motion.BeginningX >> send.Motion.BeginningY >> send.Motion.EndX >> send.Motion.EndY >> send.Motion.Length;
	return in;
}