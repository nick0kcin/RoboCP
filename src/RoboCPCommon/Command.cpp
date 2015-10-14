#pragma once
#include "Command.h"
#include <QtCore/qdatastream.h>
#include <QtXml/qdom.h>

Command::Command()
{
  ComType = 0;
  ComCondition = 0;
  Value = 0;
  Time = time(NULL);
}

Command::Command (CommandType CType, CommandCondition CCondition, float ConditionValue)
{
  ComType = CType;
  ComCondition = CCondition;
  Value = ConditionValue;
  Time = time(NULL);
}

QDomElement Command::serialize(QDomDocument& doc)
{
	QDomElement elem = doc.createElement("Command");
	elem.setAttribute("ComType", ComType);
	elem.setAttribute("ComCondition", ComCondition);
	elem.setAttribute("Value", Value);

	return elem;
}

void Command::deserialize(const QDomElement& node)
{
	ComType = node.attribute("ComType").toInt();
	ComCondition = node.attribute("ComCondition").toInt();
	Value = node.attribute("Value").toFloat();
}

QDataStream& operator<<(QDataStream& out, const Command& com)
{
	out << com.ComType << com.ComCondition << com.Value << com.Time;
	return out;
}

QDataStream& operator>>(QDataStream& in, Command& com)
{
	in >> com.ComType >> com.ComCondition >> com.Value >> com.Time;
	return in;
}