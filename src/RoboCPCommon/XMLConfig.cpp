#include "XMLConfig.h"
#include "QtXml/qdom.h"

XMLConfig::XMLConfig ()
{
  // default values
  IP = "127.0.0.1";
  KinectPort = "6666";
  CommandPort = "6667";
  SendPort = "6668";
  CarduinoPort = "\\\\.\\COM3";
  ArducopterPort = "\\\\.\\COM4";
#ifdef PCL
#if PCL_VERSION_COMPARE(<, 1, 7, 0) //compression_Profiles_e enum is located in io namespace since 1.7.0
  CompressionProfile = pcl::octree::LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;
#else
  CompressionProfile = pcl::io::LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;
#endif
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
#ifdef PCL
	#if PCL_VERSION_COMPARE(<, 1, 7, 0) //compression_Profiles_e enum is located in io namespace since 1.7.0
	using namespace pcl::octree;
	#else
	using namespace pcl::io;
	#endif
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
#ifdef PCL
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
#else
s="NO_PCL";
#endif
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
#ifdef PCL
	#if PCL_VERSION_COMPARE(<, 1, 7, 0) //compression_Profiles_e enum is located in io namespace since 1.7.0
	using namespace pcl::octree;
	#else
	using namespace pcl::io;
	#endif
#endif
	IP = node.namedItem("IP").firstChild().nodeValue();
	KinectPort = node.namedItem("KinectPort").firstChild().nodeValue();
	CommandPort = node.namedItem("CommandPort").firstChild().nodeValue();
	SendPort = node.namedItem("SendPort").firstChild().nodeValue();
	CarduinoPort = node.namedItem("CarduinoPort").firstChild().nodeValue();
	ArducopterPort = node.namedItem("ArducopterPort").firstChild().nodeValue();

	QString s = node.namedItem("CompressionProfile").firstChild().nodeValue();
#ifdef PCL
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
#endif
	if (node.namedItem("ShowStatistics").firstChild().nodeValue() == "1")
		ShowStatistics = true;
	else ShowStatistics = false;
	PointResolution = node.namedItem("PointResolution").firstChild().nodeValue().toDouble();
	OctreeResolution = node.namedItem("OctreeResolution").firstChild().nodeValue().toDouble();
	if (node.namedItem("DoVoxelGridDownDownSampling").firstChild().nodeValue() == "1")
		DoVoxelGridDownDownSampling = true;
	else DoVoxelGridDownDownSampling = false;
	IFrameRate = node.namedItem("IFrameRate").firstChild().nodeValue().toInt();
	if (node.namedItem("DoColorEncoding").firstChild().nodeValue() == "1")
		DoColorEncoding = true;
	else DoColorEncoding = false;
	ColorBitResolution = node.namedItem("ColorBitREsolution").firstChild().nodeValue().toInt();
	CameraNumber = node.namedItem("CameraNumber").firstChild().nodeValue().toInt();
	CameraFramesPerSecond = node.namedItem("CameraFramesPerSecond").firstChild().nodeValue().toInt();
	CameraFrameWidth = node.namedItem("CameraFrameWidth").firstChild().nodeValue().toInt();
	CameraFrameHeight = node.namedItem("CameraFrameHeight").firstChild().nodeValue().toInt();
}
