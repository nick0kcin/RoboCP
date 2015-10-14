#include "XMLConfig.h"
#include "QtXml\qdom.h"

XMLConfig::XMLConfig ()
{
  // default values
  IP = "127.0.0.1";
  KinectPort = "6666";
  CommandPort = "6667";
  SendPort = "6668";
  CarduinoPort = "\\\\.\\COM3";
  ArducopterPort = "\\\\.\\COM4";

#if PCL_VERSION_COMPARE(<, 1, 7, 0) //compression_Profiles_e enum is located in io namespace since 1.7.0
  CompressionProfile = pcl::octree::LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;
#else
  CompressionProfile = pcl::io::LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;
#endif

  ShowStatistics = false;
  PointResolution = 0.001;
  OctreeResolution = 0.01;
  DoVoxelGridDownDownSampling = false;
  IFrameRate = 30;
  DoColorEncoding = false;
  ColorBitResolution = 6;
  CameraNumber = 1;
  CameraFramesPerSecond = 180;
  CameraFrameWidth = 320;
  CameraFrameHeight = 240;
}

QDomElement XMLConfig::serialize(QDomDocument& doc)
{

	#if PCL_VERSION_COMPARE(<, 1, 7, 0) //compression_Profiles_e enum is located in io namespace since 1.7.0
	using namespace pcl::octree;
	#else
	using namespace pcl::io;
	#endif

	QDomElement elem = doc.createElement("XMLConfig");
	elem.setAttribute("IP", IP);
	elem.setAttribute("KinectPort", KinectPort);
	elem.setAttribute("CommandPort", CommandPort);
	elem.setAttribute("SendPort", SendPort);
	elem.setAttribute("CarduinoPort", CarduinoPort);
	elem.setAttribute("ArducopterPort", ArducopterPort);

	QString s;
	s = "LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR";

	if (CompressionProfile == LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR)
		s = "LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR";
	if (CompressionProfile == LOW_RES_ONLINE_COMPRESSION_WITH_COLOR)
		s = "LOW_RES_ONLINE_COMPRESSION_WITH_COLOR";
	if (CompressionProfile == MED_RES_ONLINE_COMPRESSION_WITHOUT_COLOR)
		s = "MED_RES_ONLINE_COMPRESSION_WITHOUT_COLOR";
	if (CompressionProfile == MED_RES_ONLINE_COMPRESSION_WITH_COLOR)
		s = "MED_RES_ONLINE_COMPRESSION_WITH_COLOR";
	if (CompressionProfile == HIGH_RES_ONLINE_COMPRESSION_WITHOUT_COLOR)
		s = "HIGH_RES_ONLINE_COMPRESSION_WITHOUT_COLOR";
	if (CompressionProfile == HIGH_RES_ONLINE_COMPRESSION_WITH_COLOR)
		s = "HIGH_RES_ONLINE_COMPRESSION_WITH_COLOR";
	if (CompressionProfile == LOW_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR)
		s = "LOW_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR";
	if (CompressionProfile == LOW_RES_OFFLINE_COMPRESSION_WITH_COLOR)
		s = "LOW_RES_OFFLINE_COMPRESSION_WITH_COLOR";
	if (CompressionProfile == MED_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR)
		s = "MED_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR";
	if (CompressionProfile == MED_RES_OFFLINE_COMPRESSION_WITH_COLOR)
		s = "MED_RES_OFFLINE_COMPRESSION_WITH_COLOR";
	if (CompressionProfile == HIGH_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR)
		s = "HIGH_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR";
	if (CompressionProfile == HIGH_RES_OFFLINE_COMPRESSION_WITH_COLOR)
		s = "HIGH_RES_OFFLINE_COMPRESSION_WITH_COLOR";

	elem.setAttribute("CompressionProfile", s);

	if (ShowStatistics)
		elem.setAttribute("ShowStatistics", "1");
	else elem.setAttribute("ShowStatistics", "0");
	elem.setAttribute("PointResolution", PointResolution);
	elem.setAttribute("OctreeResolution", OctreeResolution);
	if (DoVoxelGridDownDownSampling)
		elem.setAttribute("DoVoxelGridDownDownSampling", "1");
	else elem.setAttribute("DoVoxelGridDownDownSampling", "0");
	elem.setAttribute("IFrameRate", IFrameRate);
	if (DoColorEncoding)
		elem.setAttribute("DoColorEncoding", "1");
	else elem.setAttribute("DoColorencoding", "0");
	elem.setAttribute("ColorBitResolution", ColorBitResolution);

	elem.setAttribute("CameraNumber", CameraNumber);
	elem.setAttribute("CameraFramesPerSecond", CameraFramesPerSecond);
	elem.setAttribute("CameraFrameWidth", CameraFrameWidth);
	elem.setAttribute("CameraFrameHeight", CameraFrameHeight);

	return elem;

}

void XMLConfig::deserialize(const QDomElement& node)
{

	#if PCL_VERSION_COMPARE(<, 1, 7, 0) //compression_Profiles_e enum is located in io namespace since 1.7.0
	using namespace pcl::octree;
	#else
	using namespace pcl::io;
	#endif

	IP = node.attribute("IP");
	KinectPort = node.attribute("KinectPort");
	CommandPort = node.attribute("CommandPort");
	SendPort = node.attribute("SendPort");
	CarduinoPort = node.attribute("CarduinoPort");
	ArducopterPort = node.attribute("ArducopterPort");

	QString s = node.attribute("CompressionProfile");
	CompressionProfile = LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;

	if (s == "LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR")
		CompressionProfile = LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;
	if (s == "LOW_RES_ONLINE_COMPRESSION_WITH_COLOR")
		CompressionProfile = LOW_RES_ONLINE_COMPRESSION_WITH_COLOR;
	if (s == "MED_RES_ONLINE_COMPRESSION_WITHOUT_COLOR")
		CompressionProfile = MED_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;
	if (s == "MED_RES_ONLINE_COMPRESSION_WITH_COLOR")
		CompressionProfile = MED_RES_ONLINE_COMPRESSION_WITH_COLOR;
	if (s == "HIGH_RES_ONLINE_COMPRESSION_WITHOUT_COLOR")
		CompressionProfile = HIGH_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;
	if (s == "HIGH_RES_ONLINE_COMPRESSION_WITH_COLOR")
		CompressionProfile = HIGH_RES_ONLINE_COMPRESSION_WITH_COLOR;
	if (s == "LOW_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR")
		CompressionProfile = LOW_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR;
	if (s == "LOW_RES_OFFLINE_COMPRESSION_WITH_COLOR")
		CompressionProfile = LOW_RES_OFFLINE_COMPRESSION_WITH_COLOR;
	if (s == "MED_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR")
		CompressionProfile = MED_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR;
	if (s == "MED_RES_OFFLINE_COMPRESSION_WITH_COLOR")
		CompressionProfile = MED_RES_OFFLINE_COMPRESSION_WITH_COLOR;
	if (s == "HIGH_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR")
		CompressionProfile = HIGH_RES_OFFLINE_COMPRESSION_WITHOUT_COLOR;
	if (s == "HIGH_RES_OFFLINE_COMPRESSION_WITH_COLOR")
		CompressionProfile = HIGH_RES_OFFLINE_COMPRESSION_WITH_COLOR;

	if (node.attribute("ShowStatistics") == "1")
		ShowStatistics = true;
	else ShowStatistics = false;
	PointResolution = node.attribute("PointResolution").toDouble();
	OctreeResolution = node.attribute("OctreeResolution").toDouble();
	if (node.attribute("DoVoxelGridDownDownSampling") == "1")
		DoVoxelGridDownDownSampling = true;
	else DoVoxelGridDownDownSampling = false;
	IFrameRate = node.attribute("IFrameRate").toInt();
	if (node.attribute("DoColorEncoding") == "1")
		DoColorEncoding = true;
	else DoColorEncoding = false;
	ColorBitResolution = node.attribute("ColorBitREsolution").toInt();
	CameraNumber = node.attribute("CameraNumber").toInt();
	CameraFramesPerSecond = node.attribute("CameraFramesPerSecond").toInt();
	CameraFrameWidth = node.attribute("CameraFrameWidth").toInt();
	CameraFrameHeight = node.attribute("CameraFrameHeight").toInt();
}