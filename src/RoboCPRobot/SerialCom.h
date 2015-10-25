#pragma once
#include <tchar.h>
#include "XMLConfig.h"
#include <Windows.h> //must either include this after PCL headers or add NOMINMAX definition to project properties
					//otherwise min and max macros tamper with min() and max() methods calls

#ifdef ENABLE_LOGGING
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/raw_logging.h>
#endif

#define READ_BUFF_SIZE 256
#define SERIAL_WRITE_WAIT_MS 5000

class SerialCom
{
private:
  char *out;
  int outSize;
  HANDLE hComm;
public:
  char *Read(void);
  void Write(char *Data, int DataSize);
  int GetOutSize();
  SerialCom(char *PortName, int BaudRate);
  ~SerialCom(void);
};

