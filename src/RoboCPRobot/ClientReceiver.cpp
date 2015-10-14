#pragma once
#include <iostream>
#include "ClientReceiver.h"
#include "CommandConfig.h"
#include "QtCore/qdatastream.h"
#include <QtNetwork/qtcpserver.h>
#include "QtNetwork/qtcpsocket.h"

ClientReceiver::ClientReceiver()
{

}

void ClientReceiver::Configure(Config* commandConfig)
{
	CommandConfig* x = (CommandConfig*)commandConfig;
	port = x->getPort(); // Reading port from config
}

ClientReceiver::~ClientReceiver(void)
{}

void ClientReceiver::Start()
{

	try
	{
		QTcpServer server;
		server.listen(QHostAddress::Any, port);
		std::cout << "ClientReceiver: Waiting for connection.." << endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "ClientReceiver: Waiting for connection..");
		#endif

		server.waitForNewConnection(-1);
		QTcpSocket* socket = server.nextPendingConnection();
		std::cout << "ClientReceiver: Connected!" << endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "ClientReceiver: Connected!");
		#endif

		QDataStream inStream(socket);
		quint16 blockSize = 0;
		Command com;

		while (socket->isOpen())
		{
			if (blockSize == 0)
			{
				if (socket->bytesAvailable() < sizeof(quint16))
					continue;
				inStream >> blockSize;
			}

			if (socket->bytesAvailable() < blockSize)
				continue;

			inStream >> com;
			blockSize = 0;

			std::cout << "New command: " << com.ComType << " " << com.ComCondition << " " << com.Value << std::endl; // TODO: command buffer
			#ifdef ENABLE_LOGGING
			RAW_LOG(INFO, "New command: %d %d %f", com.ComType, com.ComCondition, com.Value);
			#endif
		}

	}
	catch (std::exception& e)
	{
		std::cout << "ClientReceiver: Exception: " << e.what() << std::endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "ClientReceiver: Exception: %s", e.what());
		#endif
	}
}