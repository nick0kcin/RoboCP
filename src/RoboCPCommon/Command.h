#pragma once
#include <time.h>

class QDomElement;
class QDomDocument;
class QDataStream;

enum CommandType
{
	MoveForward,
	Rotate,
	Stay
};

enum CommandCondition
{
	PassedTime,
	PassedDistance,
	NearObject
};

class Command
{
public:
	QDomElement serialize(QDomDocument& doc);
	void deserialize(const QDomElement& node);

	friend QDataStream& operator<<(QDataStream& out, const Command& com);
	friend QDataStream& operator>>(QDataStream& in, Command& com);

	Command(CommandType CType, CommandCondition CCondition, float ConditionValue);
	Command();
	
	int ComType;
	int ComCondition;
	float Value;
	time_t Time;
};
