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
            struct 	std::tm tm;
            gmtime_r(&com.Time,&tm);
			char timestr[9];
			sprintf(timestr,"%d:%d:%d",tm.tm_hour,tm.tm_min,tm.tm_sec);
	out << com.ComType << com.ComCondition << com.Value << timestr;
	return out;
}

QDataStream& operator>>(QDataStream& in, Command& com)
{
QString timestring;
	in >> com.ComType >> com.ComCondition >> com.Value >> timestring;
	struct 	std::tm tm;
    sscanf(timestring.toStdString().c_str(),"%d:%d:%d",&tm.tm_hour,&tm.tm_min,&tm.tm_sec);
    com.Time=mktime(&tm);
	return in;
}
