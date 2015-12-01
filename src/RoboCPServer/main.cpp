#pragma once
#include <stdarg.h>
#include "KinectViewer.h"
#include "KinectReceiver.h"
#include "KinectManager.h"
#include "SendReceiver.h"
#include "SendManager.h"
#include "CommandMaker.h"
#ifdef PCL
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#endif // PCL
#include "XMLConfig.h"

#include <QtCore/qfile.h>
#include <QtXml/qdom.h>
#ifdef BOOST
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#else
#include <thread>
#include <functional>
#endif
#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

int main(char *args[], int count)
{
  freopen ("log.log", "a", stderr);
  #ifdef ENABLE_LOGGING
  RAW_LOG (INFO, "MAIN SERVER STARTED");
  #endif

  XMLConfig config;
  { //deserialization
	  QDomDocument doc;
	  QFile file("config.xml");
	  if (file.open(QIODevice::ReadOnly | QIODevice::Text) || doc.setContent(&file))
	  {
		  QDomNodeList eNodes = doc.elementsByTagName("XMLConfig");
		  config.deserialize(eNodes.at(0).toElement());
	  }
	  else
		std::cout << "Can't find config.xml! Default config used." << std::endl;
  }

  KinectBuffer kinectBuffer (10);
  KinectViewer kinectViewer (&config); //config isn't actually used there, remove it?
  KinectReceiver kinectReceiver (&config, &kinectBuffer);
  KinectManager kinectManager (&kinectBuffer, &kinectViewer);

  CommandMaker commandMaker (&config);

  SendBuffer sendBuffer (50);
  SendReceiver sendReceiver (&config, &sendBuffer);
  SendManager sendManager (&sendBuffer, &kinectViewer);


#ifdef BOOST
  boost::thread_group tgroup;

  tgroup.create_thread ( boost::bind (&KinectViewer::Start, &kinectViewer) );

  //tgroup.create_thread ( boost::bind (&KinectReceiver::Start, &kinectReceiver) );

  tgroup.create_thread ( boost::bind (&KinectManager::Start, &kinectManager) );

  tgroup.create_thread ( boost::bind (&CommandMaker::Start, &commandMaker) );

  tgroup.create_thread ( boost::bind (&SendReceiver::Start, &sendReceiver) );

  tgroup.create_thread ( boost::bind (&SendManager::Start, &sendManager) );


  tgroup.join_all ();
  #else
  std::vector<std::thread> tgroup;
  tgroup.push_back(std::thread(std::bind (&KinectViewer::Start, &kinectViewer)));
  tgroup.push_back(std::thread(std::bind (&KinectManager::Start, &kinectManager)));
  tgroup.push_back(std::thread(std::bind (&CommandMaker::Start, &commandMaker)));
  tgroup.push_back(std::thread(std::bind (&SendReceiver::Start, &sendReceiver)));
  tgroup.push_back(std::thread(std::bind (&SendManager::Start, &sendManager)));
  for(int i=0;i<tgroup.size();i++)
  tgroup[i].join();
  #endif

  return 0;
}
