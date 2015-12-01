#pragma once
#include <QtCore/qstring.h>
#ifdef PCL
#include <pcl/pcl_config.h>
#include <pcl/compression/octree_pointcloud_compression.h>
#else
#endif
//#define ENABLE_LOGGING

class QDomElement;
class QDomDocument;

// Config class
class XMLConfig {
public:
	QDomElement serialize(QDomDocument& doc);
	void deserialize(const QDomElement& node);


	QString IP;
	QString KinectPort;
	QString CommandPort;
	QString SendPort;
	QString CarduinoPort;
	QString ArducopterPort;
#ifdef PCL

#if PCL_VERSION_COMPARE(<, 1, 7, 0) //compression_Profiles_e enum is located in io namespace since 1.7.0
	pcl::octree::compression_Profiles_e CompressionProfile;
#else
	pcl::io::compression_Profiles_e CompressionProfile;
#endif
#endif
	bool ShowStatistics;
	double PointResolution;
	double OctreeResolution;
	bool DoVoxelGridDownDownSampling;
	unsigned int IFrameRate;
	bool DoColorEncoding;
	unsigned int ColorBitResolution;

	int CameraNumber;
	int CameraFramesPerSecond;
	int CameraFrameWidth;
	int CameraFrameHeight;

	XMLConfig();
};
