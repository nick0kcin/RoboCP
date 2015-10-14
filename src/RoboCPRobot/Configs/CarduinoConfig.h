/*








//WARNING!!!!!!!! This is a template file. Do not change it without necessity.










*/
#pragma once
#include <string>
#include "Config.h"
class CarduinoConfig : public Config{
public:
  CarduinoConfig();
  friend class configFactory;
  ~CarduinoConfig();
  std::string getPort();

private:
  std::string Port;
};