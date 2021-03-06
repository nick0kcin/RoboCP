#pragma once
#include "Controller.h"
#include "NanoReceivedBuffer.h"
#include "Config.h"
#include "SerialCom.h"

#include <string.h>
#include <time.h>
#include <thread>
#include <chrono>


#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

//#define NANO_FPS_TEST
//#define NANO_TELEMETRY_TEST
//#define NANO_INPUT_DATA_TEST

const int NANO_BAUD_RATE = 115200;
const int NANO_SECONDS_TO_RECONNECT = 5;
const int TO_SEND_BUFF_SIZE = 128;

class NanoController :
  public Controller
{
private:
  char *dataToSend;
  bool readyToNewMessage;
  NanoReceivedBuffer *buffer;
  SerialCom *nanoCom;
  std::string nanoPort;
  time_t lastReadTime;
public:
  void FakeStart(void);
  void Start(void);
  bool ChangeGPSMessage(char *UTC, char *Latitude, char *Longtitude, char *GSpeed, char *SpeedAngle);
  bool SetDefaultGPSMessage();
  NanoReceivedBuffer *GetBuffer(void);
  NanoController(NanoReceivedBuffer *buf);
  void Configure(Config *carduinoConfig);
  ~NanoController(void);
};

