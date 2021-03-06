#include <iostream>
#include "QtCore/qdatastream.h"
#include "QtNetwork/qtcpserver.h"
#include "QtNetwork/qtcpsocket.h"
#include "SendSender.h"
#include "SendConfig.h"

SendSender::SendSender(SendBuffer * buf)
{
	buffer = buf;
}

void SendSender::Configure(Config* sendConfig)
{
	SendConfig* x = (SendConfig*)sendConfig;
	port = x->getPort(); //reading port from config
}

SendSender::~SendSender(void)
{}

void SendSender::Start()
{
	try
	{
		QTcpServer server;
		server.listen(QHostAddress::Any, port);
		std::cout << "SendSender: Waiting for connection.." << std::endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "SendSender: Waiting for connection..");
		#endif

		server.waitForNewConnection(-1);
		QTcpSocket* socket = server.nextPendingConnection();

		std::cout << "SendSender: Connected!" << std::endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "SendSender: Connected!");
		#endif

		while (socket->isOpen())
		{
		#ifdef BOOST
			boost::shared_ptr<Send> sendData;
			#else
			std::shared_ptr <Send> sendData;
			#endif // BOOST
			sendData = buffer->Dequeue(); // Reading Send object from buffer

			QByteArray block;
			QDataStream outStream(&block, QIODevice::ReadWrite);

			outStream << quint16(0) << *sendData;
			outStream.device()->seek(0);
			outStream << (quint16)(block.size() - sizeof(quint16));
			socket->write(block);
			socket->waitForBytesWritten(5000);
			block.clear();
			outStream.device()->reset();
	}
}
	catch (std::exception& e)
	{
		std::cout << "SendSender: Exception: " << e.what() << std::endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "SendSender: Exception: %s", e.what());
		#endif
	}

}
