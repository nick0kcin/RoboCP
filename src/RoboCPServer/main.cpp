#pragma once
#include <stdarg.h>
#include "KinectViewer.h"
#include "KinectReceiver.h"
#include "KinectManager.h"
#include "SendReceiver.h"
#include "SendManager.h"
#include "CommandMaker.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include "XMLConfig.h"

#include <QtCore/qfile.h>
#include <QtXml/qdom.h>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

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
		cout << "Can't find config.xml! Default config used." << endl;	 
  }

  KinectBuffer kinectBuffer (10);
  KinectViewer kinectViewer (&config); //config isn't actually used there, remove it?
  KinectReceiver kinectReceiver (&config, &kinectBuffer);
  KinectManager kinectManager (&kinectBuffer, &kinectViewer);

  CommandMaker commandMaker (&config);

  SendBuffer sendBuffer (50);
  SendReceiver sendReceiver (&config, &sendBuffer);
  SendManager sendManager (&sendBuffer, &kinectViewer);



  boost::thread_group tgroup;

  tgroup.create_thread ( boost::bind (&KinectViewer::Start, &kinectViewer) );

  //tgroup.create_thread ( boost::bind (&KinectReceiver::Start, &kinectReceiver) );

  tgroup.create_thread ( boost::bind (&KinectManager::Start, &kinectManager) );

  tgroup.create_thread ( boost::bind (&CommandMaker::Start, &commandMaker) );

  tgroup.create_thread ( boost::bind (&SendReceiver::Start, &sendReceiver) );

  tgroup.create_thread ( boost::bind (&SendManager::Start, &sendManager) );


  tgroup.join_all ();

  return 0;
}