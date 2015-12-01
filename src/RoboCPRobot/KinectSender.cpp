#include "KinectSender.h"
#include "KinectConfig.h"
#include "KinectData.h"
#include "OctreeEncoderConfig.h"
#include "QtCore/qdatastream.h"
#include "QtNetwork/qtcpserver.h"
#include "QtNetwork/qtcpsocket.h"
#include <iostream>
#include <ctime>

KinectSender::KinectSender(KinectBuffer * buf)
{
	buffer = buf;
}

void KinectSender::Configure(Config* kinectConfig, Config* octreeConfig)
{

	KinectConfig* kinectCfg = (KinectConfig*)kinectConfig;
	OctreeEncoderConfig* octreeCfg = (OctreeEncoderConfig*)octreeConfig;

	port = kinectCfg->getPort(); //Reading port from config

	// We will encode point clouds before sending via octreeCoder
	// Parameters for constructor are taken from config
	#ifdef PCL
	#if PCL_VERSION_COMPARE(<, 1, 7, 0)
	octreeCoder = new pcl::octree::PointCloudCompression<pcl::PointXYZ>(octreeCfg->getCompressionProfile(), octreeCfg->getShowStatistics(),
		octreeCfg->getPointResolution(), octreeCfg->getOctreeResolution(),
		octreeCfg->getDoVoxelGridDownDownSampling(), octreeCfg->getIFrameRate(),
		octreeCfg->getDoColorEncoding(), octreeCfg->getColorBitResolution());
	#else
	octreeCoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(octreeCfg->getCompressionProfile(), octreeCfg->getShowStatistics(),
		octreeCfg->getPointResolution(), octreeCfg->getOctreeResolution(),
		octreeCfg->getDoVoxelGridDownDownSampling(), octreeCfg->getIFrameRate(),
		octreeCfg->getDoColorEncoding(), octreeCfg->getColorBitResolution());;
	#endif
    #endif // PCL
}

void KinectSender::Start()
{
	try
	{
		QTcpServer server;
		server.listen(QHostAddress::Any, port);
		std::cout << "KinectSender: Waiting for connection.." << endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "KinectSender: Waiting for connection..");
		#endif
		server.waitForNewConnection(-1);
		QTcpSocket* socket = server.nextPendingConnection();

		std::cout << "KinectSender: Connected!" << endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "KinectSender: Connected!");
		#endif

		while (socket->isOpen())
		{
		#ifdef BOOST
			boost::shared_ptr<KinectData> pdata;
			#else
			std::shared_ptr<KinectData> pdata;
			#endif // BOOST
			pdata = buffer->Dequeue(); // Read KinectData from buffer

			QByteArray block;
			QDataStream outStream(&block, QIODevice::ReadWrite);

			outStream << quint16(0);
	    	struct 	std::tm tm;
	    	gmtime_r(&(pdata->Time),&tm);
			char timestr[9];
			sprintf(timestr,"%d:%d:%d",tm.tm_hour,tm.tm_min,tm.tm_sec);
			outStream <<timestr; // Send time
			//octreeCoder->encodePointCloud(pdata->Cloud, socketStream); // Then send point cloud
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
		std::cout << "KinectSender: Exception: " << e.what() << endl; //TODO: write in log
		#ifdef ENABLE_LOGGING
		RAW_LOG(INFO, "KinectSender: Exception: %s", e.what());
		#endif
	}

}

KinectSender::~KinectSender(void)
{
#ifdef PCL
	delete (octreeCoder);
	#endif // PCL
}
