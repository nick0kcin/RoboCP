#pragma once
#include <thread>
#include <chrono>
#include "KinectReceiver.h"
#include "KinectData.h"
#include "XMLConfig.h"
#include "QtCore/qdatastream.h"
#include "QtNetwork/qtcpserver.h"
#include "QtNetwork/qtcpsocket.h"

KinectReceiver::KinectReceiver(XMLConfig * x, KinectBuffer* b)
{
	ip = x->IP; // Reading IP from config
	port = x->KinectPort.toUShort(); // Reading port from config
	kinectBuffer = b;

	// We will receive encoded point clouds, so we need to decode them
	#if PCL_VERSION_COMPARE(<, 1, 7, 0)
	octreeCoder = new pcl::octree::PointCloudCompression<pcl::PointXYZ>(x->CompressionProfile, x->ShowStatistics, x->PointResolution,
		x->OctreeResolution, x->DoVoxelGridDownDownSampling, x->IFrameRate,
		x->DoColorEncoding, x->ColorBitResolution);
	#else
	octreeCoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(x->CompressionProfile, x->ShowStatistics, x->PointResolution,
		x->OctreeResolution, x->DoVoxelGridDownDownSampling, x->IFrameRate,
		x->DoColorEncoding, x->ColorBitResolution);
	#endif
}

KinectReceiver::~KinectReceiver ()
{
  delete (octreeCoder);
}

void KinectReceiver::Start ()
{
  try {
	  QTcpSocket socket;
	  while(socket.state() != socket.ConnectedState)
		socket.connectToHost(QHostAddress(ip), port);

      cout << "KinectReceiver: Connected!" << endl; // TODO: write in log
      #ifdef ENABLE_LOGGING
	    RAW_LOG (INFO,  "KinectReceiver: Connected!");
      #endif
		std::this_thread::sleep_for(5s);

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

		    boost::shared_ptr<KinectData> kData (new KinectData); // Creating new KinectData
		    inStream >> kData->Time; // Receivig time
			

			quint32 rawDataSize;
			inStream >> rawDataSize;
			char * encodedPC = new char[rawDataSize];
			inStream.readRawData(encodedPC, rawDataSize);
			std::string encPCString(encodedPC, rawDataSize);
			delete[] encodedPC;
			std::istringstream encPCStream;
			encPCStream.str(encPCString);
			
		    octreeCoder->decodePointCloud (encPCStream, kData->Cloud); // Then receiving point cloud
		    kinectBuffer->Enqueue (kData); // adding KinectData in KinectBuffer
	    }
  }
  catch (exception& e) {
    cout << "KinectReceiver: Exception: " << e.what () << endl; // TODO: write in log
    #ifdef ENABLE_LOGGING
	  RAW_LOG (INFO,  "KinectReceiver: Exception: %s", e.what());
    #endif
  }
}