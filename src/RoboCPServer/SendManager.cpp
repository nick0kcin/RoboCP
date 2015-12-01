#pragma once
#include "SendManager.h"


SendManager::SendManager (SendBuffer* b, KinectViewer* v)
{
  sendBuffer = b;
  kinectViewer = v;
}

SendManager::~SendManager ()
{
}

void SendManager::Start ()
{
       #ifdef BOOST
	  boost::shared_ptr<Send> sendData;
       #else
      std::shared_ptr<Send> sendData;
       #endif
	  while ( true ) {
		sendData = sendBuffer->Dequeue(); // Receiving
		kinectViewer->Mtx->lock();
		  updateText(sendData); // Updating KinectViewer info
		kinectViewer->Mtx->unlock();
	  }
}
#ifdef BOOST
void SendManager::updateText (boost::shared_ptr<Send> s)
#else
void SendManager::updateText (std::shared_ptr<Send> s)
#endif
{
  char buf[400];

  // Filling buf with sprintf, then updating text in KinectViewer
  if (s->PacketType == AccelerationPacket){
    sprintf (buf, "Acceleration x: %d", s->Acceleration.x);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 290, 10, 1, 1, 1, "AccelerationX");
    #endif
    sprintf (buf, "Acceleration y: %d", s->Acceleration.y);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 278, 10, 1, 1, 1, "AccelerationY");
    #endif
    sprintf (buf, "Acceleration z: %d", s->Acceleration.z);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 268, 10, 1, 1, 1, "AccelerationZ");
    #endif
  }
  sprintf (buf, "Top sonic: %d", s->TopSonicSensor);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 248, 10, 1, 1, 1, "TopSonic");
  #endif
  sprintf (buf, "Left sonic: %d", s->LeftSonicSensor);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 238, 10, 1, 1, 1, "LeftSonic");
  #endif
  sprintf (buf, "Right sonic: %d", s->RightSonicSensor);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 224, 10, 1, 1, 1, "RightSonic");
  #endif
  sprintf (buf, "Front sonic: %d", s->FrontSonicSensor);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 214, 10, 1, 1, 1, "FrontSonic");
  #endif
  sprintf (buf, "Back sonic: %d", s->BackSonicSensor);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 202, 10, 1, 1, 1, "BackSonic");
  #endif

  if (s->PacketType == AltitudePacket){
    sprintf (buf, "Alt barometer: %f", s->AltitudeBarometer);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 186, 10, 1, 1, 1, "AltBarometer");
    #endif
    sprintf (buf, "Alt sonic: %f", s->AltitudeSonic);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 174, 10, 1, 1, 1, "AltSonic");
    #endif
  }

  if (s->PacketType == AnglesPacket){
    sprintf (buf, "Pitch: %f", s->Pitch);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 162, 10, 1, 1, 1, "Pitch");
    #endif
    sprintf (buf, "Roll: %f", s->Roll);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 150, 10, 1, 1, 1, "Roll");
    #endif
    sprintf (buf, "Yaw: %f", s->Yaw);
    #ifdef PCL
    kinectViewer->viewer->updateText (buf, 5, 138, 10, 1, 1, 1, "Yaw");
    #endif
  }

  sprintf (buf, "Time: %s", ctime(&(s->Time)) );
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 122, 10, 1, 1, 1, "SendTime");
  #endif
  sprintf (buf, "Motion x1: %f", s->Motion.BeginningX);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 112, 10, 1, 1, 1, "BeginningX");
  #endif
  sprintf (buf, "Motion y1: %f", s->Motion.BeginningY);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 102, 10, 1, 1, 1, "BeginningY");
  #endif
  sprintf (buf, "Motion x2: %f", s->Motion.EndX);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 92, 10, 1, 1, 1, "EndX");
  #endif
  sprintf (buf, "Motion y2: %f", s->Motion.EndY);
  #ifdef PCL
  kinectViewer->viewer->updateText (buf, 5, 82, 10, 1, 1, 1, "EndY");
  #endif

}
