#pragma once
#include "Controller.h"
#include "CameraReceivedBuffer.h"
#include <sstream>

class Config;

class CameraController :
  public Controller
{
private:
  int cameraNum;
  int fps;
  int width;
  int height;
  CameraReceivedBuffer *buffer;
public:
  void Start(void);
  void FakeStart(void);

  CameraReceivedBuffer *GetBuffer(void);
  CameraController(CameraReceivedBuffer *buf);

  void Configure(Config *x);
  ~CameraController(void);
};

