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

#ifdef PCL
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
	#endif
}

KinectReceiver::~KinectReceiver ()
{
#ifdef PCL
  delete (octreeCoder);
  #endif // PCL
}

void KinectReceiver::Start ()
{
  try {
	  QTcpSocket socket;
	  while(socket.state() != socket.ConnectedState)
		socket.connectToHost(QHostAddress(ip), port);

      std::cout << "KinectReceiver: Connected!" << endl; // TODO: write in log
      #ifdef ENABLE_LOGGING
	    RAW_LOG (INFO,  "KinectReceiver: Connected!");
      #endif
		std::this_thread::sleep_for(std::chrono::seconds(5));

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
		    boost::shared_ptr<KinectData> kData (new KinectData); // Creating new KinectData
		    #else
		    std::shared_ptr<KinectData> kData (new KinectData);
		    #endif
		    QString timestring;
		    inStream >> timestring; // Receivig time
		    struct tm tm;
		    sscanf(timestring.toStdString().c_str(),"%d:%d:%d",&tm.tm_hour,&tm.tm_min,&tm.tm_sec);
            kData->Time=mktime(&tm);

			quint32 rawDataSize;
			inStream >> rawDataSize;
			char * encodedPC = new char[rawDataSize];
			inStream.readRawData(encodedPC, rawDataSize);
			std::string encPCString(encodedPC, rawDataSize);
			delete[] encodedPC;
			std::istringstream encPCStream;
			encPCStream.str(encPCString);
			#ifdef PCL
		    octreeCoder->decodePointCloud (encPCStream, kData->Cloud); // Then receiving point cloud
		    #endif
		    kinectBuffer->Enqueue (kData); // adding KinectData in KinectBuffer
	    }
  }
  catch (std::exception& e) {
    std::cout << "KinectReceiver: Exception: " << e.what () << endl; // TODO: write in log
    #ifdef ENABLE_LOGGING
	  RAW_LOG (INFO,  "KinectReceiver: Exception: %s", e.what());
    #endif
  }
}
