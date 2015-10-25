#pragma once
#include "CommandMaker.h"
#include "Command.h"
#include "XMLConfig.h"
#include "QtCore/qdatastream.h"
#include "QtNetwork/qtcpserver.h"
#include "QtNetwork/qtcpsocket.h"

CommandMaker::CommandMaker(XMLConfig * x)
{
	ip = x->IP; // Reading IP from config
	port = x->CommandPort.toUShort(); // Readin port from config
}

CommandMaker::~CommandMaker()
{}

void CommandMaker::Start()
{
	try
	{
		QTcpSocket socket;
		while (socket.state() != QTcpSocket::ConnectedState)
			socket.connectToHost(QHostAddress(ip), port);

		cout << "CommandMaker: Connected!" << endl; // TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "CommandMaker: Connected!");
		#endif


		Command com;

		while (socket.isOpen())
		{
			// Reading command
			cout << "input command type (int):" << endl;
			cin >> com.ComType;
			cout << "input command condition (int):" << endl;
			cin >> com.ComCondition;
			cout << "input condition value (float):" << endl;
			cin >> com.Value;

			QByteArray block;
			QDataStream outStream(&block, QIODevice::ReadWrite);

			outStream << quint16(0) << com;
			outStream.device()->seek(0);
			outStream << (quint16)(block.size() - sizeof(quint16));
			socket.write(block);
			socket.waitForBytesWritten(5000);
		}
	}
	catch (exception& e)
	{
		cout << "CommandMaker: Exception: " << e.what() << endl; // TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "CommandMaker: Exception: %s", e.what());
		#endif
	}
}
