/*








//WARNING!!!!!!!! This is a template file. Do not change it without necessity.










*/
#pragma once
#include <string>
#include "Config.h"
class ArducopterConfig : public Config{
public:
  ArducopterConfig();
  friend class configFactory;
  ~ArducopterConfig();
  std::string getPort();
  bool getIsAvailable();
  bool getDoFakeStart();

private:
  std::string Port;
  bool IsAvailable;
  bool DoFakeStart;
};