#include "XMLConfig.h"


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