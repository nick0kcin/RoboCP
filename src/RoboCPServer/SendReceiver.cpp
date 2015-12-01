#pragma once
#include <thread>
#include <chrono>
#include "SendReceiver.h"
#include "XMLConfig.h"
#include "QtNetwork/qtcpserver.h"
#include "QtNetwork/qtcpsocket.h"

SendReceiver::SendReceiver (XMLConfig * x, SendBuffer * b)
{
  ip = x->IP; // Reading IP from config
  port = x->SendPort.toUShort(); // Reading port from config
  sendBuffer = b;
}

SendReceiver::~SendReceiver ()
{
}

void SendReceiver::Start ()
{
  try {
	  QTcpSocket socket;
	  while (socket.state() != QTcpSocket::ConnectedState)
		  socket.connectToHost(QHostAddress(ip), port);

      std::cout << "SendReceiver: Connected!" << endl; // TODO: write in log
      #ifdef ENABLE_LOGGING
	    RAW_LOG (INFO, "SendReceiver: Connected!");
      #endif
		std::this_thread::sleep_for(std::chrono::seconds(6));

		QDataStream inStream(&socket);
		quint16 blockSize = 0;

	    while (socket.isOpen()) {
			if (blockSize == 0)
			{
				if (socket.bytesAvailable() < sizeof(quint16))
					continue;
				inStream >> blockSize;
			}

			if (socket.bytesAvailable() < blockSize)
				continue;
				#ifdef BOOST
		    boost::shared_ptr<Send> sendData (new Send);  // Creating new Send object
		    #else
		    std::shared_ptr<Send> sendData (new Send);  // Creating new Send object
		    #endif
		    inStream >> *sendData; // Receiving
	    	sendBuffer->Enqueue (sendData); // Adding Send in buffer
	    }
  }
  catch (std::exception& e) {
    std::cout << "SendReceiver: Exception: " << e.what () << endl; // TODO: write in log
    #ifdef ENABLE_LOGGING
	  RAW_LOG (INFO, "SendReceiver: Exception: %s", e.what());
    #endif
  }
}
