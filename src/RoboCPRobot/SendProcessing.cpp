#include <thread>
#include <chrono>
#include "SendProcessing.h"


SendProcessing::SendProcessing(NanoReceivedBuffer *nano, ArduCopterBuffer *ardu, CameraReceivedBuffer *camera, SendBuffer *send)
{
  nanoBuffer = nano;
  arduBuffer = ardu;
  sendBuffer = send;
  cameraBuffer = camera;
}

void SendProcessing::Start()
{
#ifdef BOOST
	boost::shared_ptr <ArduCopterReceived> arduData (new ArduCopterReceived);
	boost::shared_ptr <NanoReceived> nanoData (new NanoReceived);
	boost::shared_ptr <CameraReceived> cameraData (new CameraReceived);
	#else
	std::shared_ptr <ArduCopterReceived> arduData (new ArduCopterReceived);
	std::shared_ptr <NanoReceived> nanoData (new NanoReceived);
	std::shared_ptr <CameraReceived> cameraData (new CameraReceived);
  #endif
    while (true){
    #ifdef BOOST
	  boost::shared_ptr <Send> sendData(new Send);
	  #else
	  std::shared_ptr <Send> sendData(new Send);
	  #endif // BOOST
	  sendData->Time = time(NULL);
#ifdef BOOST
	  if (arduBuffer->Used->try_wait()){
		arduBuffer->Used->post();
        arduData = arduBuffer->Dequeue();
	  }
	  #else
	  if (arduBuffer->Used->tryAcquire()){
		arduBuffer->Used->release();
        arduData = arduBuffer->Dequeue();
	  }
	  #endif // BOOST
        sendData->Acceleration = arduData->Acceleration;
		sendData->Roll = arduData->Roll;
		sendData->Pitch = arduData->Pitch;
		sendData->Yaw = arduData->Yaw;
		sendData->AltitudeSonic = arduData->AltitudeSonic;
		sendData->AltitudeBarometer = arduData->AltitudeBarometer;
    sendData->PacketType = arduData->PacketType;
#ifdef BOOST
	  if (nanoBuffer->Used->try_wait()){
		nanoBuffer->Used->post();
	    nanoData = nanoBuffer->Dequeue();
	  }
	  #else
	  if (nanoBuffer->Used->tryAcquire()){
		nanoBuffer->Used->release();
	    nanoData = nanoBuffer->Dequeue();
	  }
	  #endif // BOOST
        sendData->TopSonicSensor = nanoData->TopSonicSensor;
		sendData->FrontSonicSensor = nanoData->FrontSonicSensor;
		sendData->LeftSonicSensor = nanoData->LeftSonicSensor;
		sendData->RightSonicSensor = nanoData->RightSonicSensor;
		sendData->BackSonicSensor = nanoData->BackSonicSensor;
#ifdef BOOST
		if (cameraBuffer->Used->try_wait()){
		  cameraBuffer->Used->post();
		  cameraData = cameraBuffer->Dequeue();
		}
		#else
        if (cameraBuffer->Used->tryAcquire()){
		  cameraBuffer->Used->release();
		  cameraData = cameraBuffer->Dequeue();
		}
		#endif // BOOST
		sendData->Motion = cameraData->Motion;

      sendBuffer->Enqueue (sendData);
      //Sleep (50);
	  std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

SendProcessing::~SendProcessing(void)
{
}
