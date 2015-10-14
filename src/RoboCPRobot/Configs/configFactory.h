/*








//WARNING!!!!!!!! This is a template file. Do not change it without necessity.










*/
#pragma once
#include<QtCore/qhash.h>
#include "Config.h"

class QJsonObject;

//Main class of processing config
class configFactory{
public:
  //configName - name of device
  Config* ConfigByName(QString configName);
  configFactory();
  ~configFactory();
  void Parse();
private:
  QHash<QString, Config*> MapOfConfigs;
  Config* DetermineConfigObject(QJsonObject treeOfObject);
};