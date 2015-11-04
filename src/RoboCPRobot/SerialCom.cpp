#include "SerialCom.h"

SerialCom::SerialCom(char *PortName, int BaudRate)
{
  out = new char[READ_BUFF_SIZE];
  outSize = 0;
  #ifdef ENABLE_LOGGING
  RAW_LOG (INFO, "SerialCom(%s): connecting...",PortName);
  #endif
  //hComm = CreateFile(pcCommPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
  hComm=open(PortName,O_RDWR|O_NOCTTY);
  if (hComm == -1){
      #ifdef ENABLE_LOGGING
      RAW_LOG (INFO, "SerialCom(%s): can't connect - this com port or device doesn't exist",PortName);
      #endif
  }else{
    #ifdef ENABLE_LOGGING
    RAW_LOG (INFO, "SerialCom(%s): connected!",PortName);
    #endif
  fcntl(hComm,F_SETFL,FNDELAY);
tcgetattr(hComm,&optold);
bzero(&optnew,sizeof(optnew));
optnew=optold;
cfsetspeed(&optnew,BaudRate);
optnew.c_cflag &=  ~CSIZE;
optnew.c_cflag|= CS8; //8 bit, no parity,1 stopbit
optnew.c_cflag&= ~CSTOPB;
optnew.c_cflag&=~PARENB;
optnew.c_cflag|=CRTSCTS;// enable RTS/CTS flow control
optnew.c_iflag|=IGNPAR;// ignore parity errors
optnew.c_iflag&=~IXON; //no IXON
optnew.c_iflag&=~IXOFF;// no IXOFF
optnew.c_iflag|=IGNBRK;//ignore breaking
optnew.c_oflag=0;
optnew.c_lflag=ICANON;
optnew.c_cc[VTIME]=1;//max timeout between symbols
optnew.c_cc[VMIN]=(unsigned int)(READ_BUFF_SIZE-1);//reading block size
cfmakeraw(&optnew);
if(tcflush(hComm,TCIOFLUSH)<0)
{
#ifdef ENABLE_LOGGING
    RAW_LOG (INFO, "SerialCom(%s): can not flush",PortName);
    #endif
}
if(tcsetattr(hComm,TCSANOW,&optnew)<0)
{
 #ifdef ENABLE_LOGGING
    RAW_LOG (INFO, "SerialCom(%s): can not apply setings",PortName);
    #endif
}
//  COMMCONFIG conf;
//  conf.dcb.DCBlength = sizeof(DCB);
//  GetCommState(hComm, &conf.dcb);
//  conf.dcb.BaudRate = BaudRate;              // Current baud
//  conf.dcb.fBinary = TRUE;               // Binary mode; no EOF check
//  conf.dcb.fParity = FALSE;               // Enable parity checking    //tty.c_cflag     &=  ~PARENB
//  conf.dcb.fOutxCtsFlow = FALSE;         // No CTS output flow control
//  conf.dcb.fOutxDsrFlow = FALSE;         // No DSR output flow control
//  conf.dcb.fDtrControl = DTR_CONTROL_ENABLE; // DTR flow control type
//  conf.dcb.fDsrSensitivity = FALSE;      // DSR sensitivity
//  conf.dcb.fTXContinueOnXoff = FALSE;     // XOFF continues Tx
//  conf.dcb.fOutX = FALSE;                // No XON/XOFF out flow control
//  conf.dcb.fInX = FALSE;                 // No XON/XOFF in flow control
//  conf.dcb.fErrorChar = FALSE;           // Disable error replacement
//  conf.dcb.fNull = FALSE;                // Disable null stripping
//  conf.dcb.fRtsControl = RTS_CONTROL_ENABLE; // RTS flow control
//  conf.dcb.fAbortOnError = FALSE;        // Do not abort reads/writes on error
//  conf.dcb.ByteSize = 8;                 // Number of bits/byte, 4-8
//
//  conf.dcb.Parity = NOPARITY;            // 0-4=no,odd,even,mark,space
//  conf.dcb.StopBits = ONESTOPBIT;
//  if (!SetCommState(hComm, &conf.dcb)){
//    #ifdef ENABLE_LOGGING
//    RAW_LOG (INFO, "SerialCom(%s): can't set comm state",PortName);
//    #endif
//  }
//  COMMTIMEOUTS commTimeouts;
//  GetCommTimeouts(hComm, &commTimeouts);
//  commTimeouts.ReadIntervalTimeout = 1;
//  commTimeouts.ReadTotalTimeoutMultiplier = 0;
//  commTimeouts.ReadTotalTimeoutConstant = 0;
//  commTimeouts.WriteTotalTimeoutMultiplier = 0;
//  commTimeouts.WriteTotalTimeoutConstant = 0;
//  if (!SetCommTimeouts(hComm,&commTimeouts)){
//    #ifdef ENABLE_LOGGING
//    RAW_LOG (INFO, "SerialCom(%s): can't set timeouts",PortName);
//    #endif
//  }


  delete [] PortName;
  sleep(3);
  }
}

char *SerialCom::Read(void)
{

int toRead=READ_BUFF_SIZE-1;
outSize=read(hComm,out,toRead);
if(outSize<toRead)
{
 #ifdef ENABLE_LOGGING
    RAW_LOG (INFO, "SerialCom(%s): some data lost",PortName);
    #endif
}

//  COMSTAT status;
//  DWORD errors;
//  DWORD bytesRead;
//  DWORD toRead;
//  OVERLAPPED osReader = {0};
//  osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
//  ClearCommError(hComm, &errors, &status);
//  outSize = 0;
//  if (status.cbInQue>=1){
//    if (status.cbInQue<READ_BUFF_SIZE-1){
//      toRead = status.cbInQue;
//    }else{
//      toRead = READ_BUFF_SIZE-1;
//    }
//    ReadFile(hComm,out,toRead, &bytesRead, &osReader);
//    outSize = bytesRead;
//  }
//  CloseHandle(osReader.hEvent);
  return out;
}

void SerialCom::Write(char *Data, int DataSize)
{

int written=write(hComm,Data,DataSize);
if(written<0)
{
 #ifdef ENABLE_LOGGING
    RAW_LOG (INFO, "SerialCom(%s): cannot write data",PortName);
    #endif
}


//  DWORD dwBytesWritten;
//  OVERLAPPED osWriter = {0};
//  osWriter.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
//  WriteFile(hComm, &Data[0], DataSize, &dwBytesWritten, &osWriter);
//  WaitForSingleObject(osWriter.hEvent, SERIAL_WRITE_WAIT_MS);
//  CloseHandle(osWriter.hEvent);
}

int SerialCom::GetOutSize(void)
{
  return outSize;
}

SerialCom::~SerialCom(void)
{
tcsetattr(hComm,TCSANOW,&optold);
  close(hComm);
  delete [] out;
}
